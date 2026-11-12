# ft_malloc: design notes

How the allocator is built, and why. For building and using the library, see the [README](README.md).

## What it is

`libft_malloc.so` replaces libc's `malloc`, `free` and `realloc`, and adds `show_alloc_mem`, which prints the current state of the heap. Loaded through `LD_LIBRARY_PATH` (or `LD_PRELOAD`), it serves every allocation of an unmodified program.

The operating system only gives memory in pages, through `mmap`. A system call per `malloc` would be slow, and a whole page for 24 bytes would waste memory. The allocator sits between the two: it requests large regions rarely, then hands out small pieces of them with pointer arithmetic. It trades a little memory (headers, pre-allocation) for far fewer system calls, and every choice below is about keeping that trade worthwhile.

## Architecture

Memory is organised in three levels, each one a header placed directly in front of the memory it describes:

```
marena (global)
 ├── TINY   (≤ 128 B,  ≥ 100 chunks per region)  mregion ⇄ mregion ⇄ …
 ├── SMALL  (≤ 1024 B, ≥ 100 chunks per region)  mregion ⇄ mregion ⇄ …
 └── LARGE  (> 1024 B, one region per allocation) mregion ⇄ mregion ⇄ …

mregion = [ header | mchunk | mchunk | mchunk | … ]   (one mmap, page-rounded)
mchunk  = [ header | user data ]                       (USED, or FREE and in the mbin)
```

- **marena**: the entry point. It holds the head of each region list.
- **mregion**: one `mmap` call, rounded up to the page size. Regions of a class form a doubly linked list. Each keeps its own **mbin**, the address-ordered list of its free chunks, and a count of used chunks.
- **mchunk**: the header in front of each block handed to the user.

```c
typedef struct s_mchunk
{
    usage_state_t   state;
    size_t          prev_allocation_size;
    size_t          allocation_size;
    struct s_mchunk *next_free_mchunk;
    struct s_mchunk *prev_free_mchunk;
} mchunk_t;
```

- `state` is `FREE` or `USED`.
- `allocation_size` is the size the user asked for. A chunk spans `MCHUNK_HEADER_SIZE + ALIGN_UP(allocation_size, ALIGNMENT_BOUNDARY)` bytes, so the next chunk is reached in O(1) by pointer arithmetic. Any in-place resize must keep that span unchanged.
- `prev_allocation_size` gives the same O(1) access to the previous chunk.
- `next_free_mchunk` / `prev_free_mchunk` link the chunk into its region's mbin, and are only meaningful while it is free.

```c
#define GET_MCHUNK_DATA_PTR(c) ((void*)((unsigned char*)(c) + MCHUNK_HEADER_SIZE))
#define GET_MCHUNK_PTR(p)      ((mchunk_t*)((unsigned char*)(p) - MCHUNK_HEADER_SIZE))
```

## How an allocation flows

- **`malloc(n)`** rejects aberrant sizes, takes the global lock, and initialises the arena on first use. The size selects the class and its region list. The allocator walks the regions, asks each region's mbin for a fitting free chunk, and only calls `mmap` for a new region when none fits. The chosen chunk is split if it is larger than needed, and the remainder goes back to the mbin.
- **`free(p)`** takes the lock, recovers the header from the pointer, and checks that it belongs to the arena and is in use. Otherwise it reports `double free or corruption` instead of corrupting the heap. It then marks the chunk free and merges it with its free neighbours. An empty region is returned to the OS, except the ones kept warm (see below).
- **`realloc(p, n)`** applies the same checks as `free`, then resizes in place when it can, or moves the data to a new chunk.

The lock is taken before the arena is initialised and before a pointer is inspected, so no thread ever reads region lists or chunk headers while another one changes them.

## Design choices and trade-offs

| Choice | Why, and what it costs |
|---|---|
| Size classes (TINY ≤ 128 B, SMALL ≤ 1024 B, LARGE) | Small blocks of similar size share pre-allocated regions of at least 100 chunks, so most small allocations cost no system call and fragment less. LARGE blocks get their own region, sized exactly, because their size is unpredictable. |
| 16-byte alignment, page-rounded regions | Every returned pointer is aligned like libc's, so any type can be stored. All sizes go through one set of macros (`ALIGN_UP`, `GET_MCHUNK_SIZE`), so alignment logic lives in one place. |
| One free list per region, not one global list | A search only touches regions of the right class, and a region knows instantly whether it is full (empty mbin) or unused (zero used chunks), which drives when it can be returned to the OS. |
| First fit for TINY, best fit for SMALL and LARGE | TINY chunks are nearly all the same size, so the first fitting chunk is good enough and fastest. For larger sizes a closer fit wastes less memory, which is worth a longer scan. The strategy is a function pointer chosen per class, so it can be changed in one place. |
| Coalescing on free | A freed chunk is merged with its free neighbours, so the region does not degrade into fragments too small to reuse. |
| Keep one region per bound class, unmap the rest | Keeping a warm TINY and SMALL region avoids an `mmap` / `munmap` cycle in programs that allocate and free in a loop. Empty LARGE regions are returned immediately, since their size is unlikely to be reused. |
| `realloc` in place when possible | Within the same class, a chunk shrinks by splitting or grows by absorbing free neighbours. Only when it changes class or has no room does the data move to a new chunk. |
| Thread safety: one global mutex | My first version gave each thread its own arena (`_Thread_local`), with no lock contention. The subject asks for a global lock, so I switched to one arena behind a single `pthread_mutex`: simpler and correct, but threads now wait for each other on every call. Both are valid; the choice depends on the workload. |
| Hidden internal symbols | Internals are compiled with `#pragma GCC visibility push(hidden)` and libft_mini with `-fvisibility=hidden`, so only the four public functions are exported and nothing can clash with the host program. |

The fit strategy, chosen per size class:

```c
mchunk_t *select_best_fit_mbin_mchunk(mchunk_t *mbin, size_t allocation_size)
{
    mchunk_t *(*strategy)(mchunk_t*, size_t);

    if (allocation_size <= TINY_MCHUNK_MAX_ALLOCATION_SIZE)
        strategy = fn_select_mbin_mchunk_first_fit;
    else
        strategy = fn_select_mbin_mchunk_best_fit;
    return strategy(mbin, allocation_size);
}
```

## How it is tested

A separate program in `test/`, linked against the library, with one suite per area: `macros`, `malloc`, `realloc`, `free`. Each case runs in its own thread and prints what it did, what was expected and what it got, followed by a PASS or FAIL line. The tester ends with a summary and exits non-zero if any check failed. `make std` builds the same suites against libc's `malloc`, so both outputs can be compared.

- **macros**: every configurable and derived constant (powers of two, alignment, region sizes, header sizes, pointer offsets).
- **malloc**: sizes around every boundary that matters: 0, 1 and 2 bytes, the chunk header size, the alignment boundary, the page size, the TINY/SMALL/LARGE limits, `SIZE_MAX` and the maximum size a region can hold (expected to fail cleanly with `ENOMEM`). Also filling whole regions to force new ones.
- **free**: invalid and corrupted pointers, double frees, release of empty regions, and coalescing of neighbours.
- **realloc**: `realloc(NULL, n)` and `realloc(ptr, 0)`, same size, growing and shrinking in place through coalescing or partitioning, with a blocking neighbour, across size classes, and chained growth. Data must survive every move.

Error messages are captured by redirecting `stderr` into a pipe for the duration of the call. The `show_alloc_mem` dumps are still read by eye.

## Limits and what I would do next

- **Lock contention**: one mutex serialises all threads. Next step: per-thread arenas with a shared fallback, as glibc does.
- **Linear scans**: searching a region's mbin is O(n), `free` checks a pointer against every region, and a LARGE allocation walks every LARGE region. Segregated bins by size and an address-ordered region index would make most lookups O(1) or O(log n).
- **Region search order**: regions are walked in order. Keeping regions that still have free space at the front of the list would shorten searches under load.
- **No `calloc`**: programs that call it get libc's memory, which this allocator's `free` then rejects as foreign.
