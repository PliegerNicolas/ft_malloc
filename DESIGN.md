# ft_malloc: design notes

How the allocator works and why. For building, testing and usage, see the [README](README.md).

## 1. Overview

`libft_malloc.so` replaces libc's `malloc`, `free` and `realloc`, and adds `show_alloc_mem`, which prints the allocated blocks.

The kernel offers two ways to get memory: `brk`/`sbrk`, which grow one contiguous heap, and `mmap`, which creates independent mappings of whole pages *(the [README](README.md) compares them)*. We use `mmap` and `munmap` only for ease of implementation.

One `mmap` per `malloc` would be slow *(a system call each time)* and wasteful *(a 24-byte block would take a 4 KB page)*. So the allocator maps large regions rarely and cuts them into blocks itself, trading a little memory *(headers, pre-allocated space)* for far fewer system calls.

## 2. Architecture

```
marena (one global instance, protected by a mutex)
 ├── TINY  regions:  blocks up to 128 B,  at least 100 blocks per region
 ├── SMALL regions:  blocks up to 1024 B, at least 100 blocks per region
 └── LARGE regions:  blocks above 1024 B, one block per region

region = [ region header | chunk | chunk | chunk | ... ]   (one mmap, rounded up to host's page size)
chunk  = [ chunk header  | user data ]                     (in use, or free)
```

Each header sits directly in front of what it describes, because `free` and `realloc` only receive the user's pointer: the chunk header is one subtraction away.

- **marena**: holds the head of each class's region list. A single global instance shared by all threads, so memory freed by one thread can be reused by any other.
- **mregion** *(region)*: one `mmap`, rounded to whole pages since `mmap` works in pages. A class's regions form a doubly linked list, so an empty region can be unlinked from the middle in constant time. Each region keeps:
  - its **mbin**, the list of its free chunks, **sorted by address**: the free chunk before another in the list is then also the closest free chunk before it in memory, which is how `free` finds the previous neighbour to merge with;
  - `max_free_allocation_size`, an upper limit on its largest free chunk, to skip the region without walking its list *(section 4)*;
  - its number of chunks in use, to know in constant time when it is empty.
- **mchunk** *(chunk)*: the state *(free or in use, to detect double frees)*, `allocation_size` *(the size asked for, used by `show_alloc_mem` and `realloc`)*, the free-list links, and `prev_allocation_size` *(kept up to date, but currently only used to detect corrupted headers)*.

A chunk spans `MCHUNK_HEADER_SIZE + ALIGN_UP(allocation_size)` bytes and chunks are contiguous, so the next one is found by adding that span, without a pointer.

Sizes are aligned on 16 bytes, like libc, so a block can hold any C type, including SSE types and `long double`.

## 3. How each call works

Each call takes the global mutex first, even before checking the pointer: otherwise another thread could unmap a region during the check, and a valid pointer would be reported as invalid. It slows down multi-threaded processes considerably, but keeps the implementation simple and still useful for most of my use cases.

**`malloc(size)`**

1. The size picks the class.
2. **LARGE**: a region sized for this block is mapped and put at the head of the list. No search is needed, since LARGE regions are never shared *(section 5)*, and the head is reached without walking the list.
3. **TINY / SMALL**: the class's regions are walked, skipping those whose `max_free_allocation_size` is too small. In each, the mbin is searched for a free chunk of exactly the right aligned size *(used as is)* or big enough to split *(larger by at least a header)*. Anything in between is unusable: the leftover could not hold a header.
4. If no region fits, a new one is mapped at the end of the list, so older regions and their holes keep being searched first.
5. A chunk larger than needed is split, and the rest returns to the mbin.

**`free(ptr)`**

1. The region containing the address is looked up. This is also the validity check, done before reading the header, because reading in front of a foreign pointer could crash. An unknown address is reported as `double free or corruption`.
2. A chunk not in use is reported the same way, instead of corrupting the free lists.
3. The chunk is marked free and merged with free neighbours, so the region does not break into fragments too small to reuse.
4. An empty region is unmapped, unless it is the only TINY or SMALL region left, which is kept so that allocate/free loops do not map and unmap it every time. LARGE regions are always unmapped: the next block will likely have another size.

**`realloc(ptr, size)`**

1. The pointer is validated as in `free`.
2. Within the same class, the chunk is resized in place to avoid a copy: it shrinks by splitting off its end, or grows by merging with the free chunk after it.
3. Otherwise, or without room, the data moves to a new chunk and the old one is freed.

## 4. Design choices

| Choice | Why, and what it costs |
|---|---|
| TINY ≤ 128 B, SMALL ≤ 1024 B | Small blocks are the most frequent, so pre-allocating for them saves the most system calls. Configurable in `macros.h`. |
| ≥ 100 blocks per TINY/SMALL region | One `mmap` serves at least 100 allocations, and the region header and page rounding stay small next to the region's content. |
| One region per LARGE block | Large sizes are unpredictable, so sharing regions would leave unusable gaps. Costs an `mmap` and a `munmap` per block. |
| First fit for TINY, best fit above | TINY sizes are nearly uniform, so the first fit is as good as any and fastest. Varied larger sizes waste less with the closest fit, worth a longer search. |
| A free list per region | Searches stay within the right class, and each region knows on its own whether it is full or empty. |
| `max_free_allocation_size` as an upper limit | An exact maximum would need a rescan after each allocation. The limit is raised when a free chunk appears or grows, and lowered when a search fails *(which proves nothing larger is there)*. Skipping regions this way removes most of the search time in busy heaps. |
| New TINY/SMALL regions at the end | Older holes are reused before fresh space: less memory, empty regions get unmapped, but searches are longer. |
| One global mutex | The simplest correct way to share one heap between threads. The cost is that threads wait for each other *(section 8)*. |
| Every pointer validated | Buggy programs pass invalid and double-freed pointers, and the tests do it on purpose. Reporting them beats crashing, at the cost of a region search on each `free` and `realloc`. |
| Compile-time configuration | `static_assert`s on `macros.h` *(alignment, class order, `MALLOC_DEBUG`)* make a bad configuration fail to build, and constants are computed by the compiler instead of on every call. |
| Hidden internal symbols | Only the four public functions are exported, so a host program's own `ft_strlen`, for example, cannot replace the library's. |

## 5. Invariants

The code relies on these: each place that does carries a one-line comment.

- **An in-place resize keeps the chunk's span** *(same aligned size)*. Otherwise the chunk is split or moved. A changed span would make walking the region land inside user data.
- **Two free chunks are never adjacent**, since `free` merges neighbours. So allocation never needs to merge.
- **Free chunks have aligned sizes**, so an equal aligned size means a fit without splitting.
- **`max_free_allocation_size` is never below the largest free chunk** *(it may be above)*. Otherwise a region with room would be skipped.
- **A LARGE region holding a block is never reused, and an empty one is unmapped**, so LARGE allocations need no search.
- **A chunk can outgrow its class while growing** *(e.g. a TINY chunk merged with free space in `realloc`)*, so regions are found by address, not by size.

## 6. Testing

`test/` has one suite per area: `macros`, `malloc`, `realloc`, `free`. Each case prints what it did, the expected and the obtained result, then PASS or FAIL. The tester ends with a summary and a non-zero exit code on failure, for use in scripts. Allocator errors are captured from `stderr` and compared too. Only the `show_alloc_mem` dumps are still read by eye, since checking them would mean parsing them.

## 7. Performance

Compared with glibc, expect:

- **Few live blocks**: TINY and SMALL stay within about an order of magnitude of glibc, since searches are short.
- **Many live blocks**: the gap widens as the heap grows, because finding a free chunk and validating a pointer both walk lists whose length grows with the number of blocks. glibc does both in constant time *(size-sorted bins, and the owning heap read from the chunk header or the pointer's address)*.
- **LARGE blocks**: much slower, since each one costs an `mmap` and a `munmap`, and each `free` searches every region. glibc serves blocks below 128 KB from its heap without any system call.
- **Several threads**: slower, since they all wait for one lock, while glibc serves most small requests from per-thread caches without locking.

## 8. Limits and next steps

- **LARGE is slow**: each `free` searches all regions, and each block costs an `mmap` and a `munmap`. The search could probably be removed using some extra metadata.
- **One lock for all threads**: glibc avoids most locking with per-thread caches, and avoids searching bins as they are sorted by size.
- **No `calloc`**: programs that call it get libc memory, which this `free` rejects, considered foreign.
