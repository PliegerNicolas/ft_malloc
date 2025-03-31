# ft_malloc

This is a dynamic memory allocation library for C17, designed to mimic the behavior of `malloc` in libc.

## Why build one ?

The operating system provides mechanisms to allocate memory from the heap using system calls. While C offers straightforward functions that wrap these system calls, they come with both advantages and disadvantages.

### **[sbrk](https://man7.org/linux/man-pages/man2/brk.2.html):**
- Allocates memory in a contiguous manner, making arbitrary deallocation difficult and leading to inefficient long-term memory usage and fragmentation.
- Has a complex usage pattern.
- System calls introduce overhead, making them "slow".

### **[mmap](https://man7.org/linux/man-pages/man2/mmap.2.html):**
- Uses a page-based allocation strategy, making it inefficient for small memory allocations.
- System calls introduce overhead, making them "slow".

## **Objective of ft_malloc**
Our goal with **ft_malloc** is to minimize **memory fragmentation** and enhance **performance**, albeit at the cost of **memory pre-allocation** thus additional **overhead**.

### **Gains:**
- Fewer system calls through pre-allocation, enabling more efficient memory distribution via pointer arithmetic.
- Reduced fragmentation through optimized memory management techniques.
- Simplified memory management, making allocation easier to handle.

### **Losses:**
- Increased memory usage due to additional metadata for tracking and managing allocations.
- Extra memory overhead from pre-allocation.

With our **malloc** implementation, we aim to optimize memory allocation while balancing performance and efficiency.

## Internal structure

To manage our dedicated heap we split our data into the following hierarchical structure:

```
heap_t
├── arena_t
│   ├── mbin_t
│   │   └── mchunk_t, mchunk_t, mchunk_t...
│   ├── ...
│   └── mbin_t
│       └── mchunk_t, mchunk_t, mchunk_t...
├── ...
└── arena_t
    ├── mbin_t
    │   └── mchunk_t, mchunk_t, mchunk_t...
    ├── ...
    └── mbin_t
        └── mchunk_t, mchunk_t, mchunk_t...
```

- **`mchunk_t`:** Metadata about memory chunks usable by the user to store data and their state.  
- **`mbin_t`:** Doubly-linked-list of mmap() allocated memory regions. These regions are partitionned through `mchunk_t`s using pointer arthimetics and other metadata. See here below a simple schema.
![mbin_t schema](.images/mbin_schema.png)
- **`arena_t`**: Contains a arbitrarly defined fixed-size of `mbin_t`s, separated by storage size range.  
- **`heap_t`**: Root structure containing data about the portion(s) of the heap we're using with our ft_malloc implementation.  

The largest `mbin_t` category (LARGE) calls `mmap()` on each occasion to retrieve enough memory space as large bins are too big and inconsistent to be worth strategical management.

A more precise explanation of each of these structures can be found inside their relative header files.

## libft_mini

I create **libft_mini** because I am not satisfied with my original one. It can easily be replace by the real one.
This one is more minimal and follows a more modern approach, now that I know C better.

## Usage

If you want to use this malloc implementation instead of the libc's one inside existing programs you have to:
- Prepend the path where `libft_malloc.so` is located in `LD_LIBRARY_PATH` environment variable. Ensure our *.so file is read first and has precedence.
- Ensure the existing program only uses functions that are present in the header file of libc's malloc and ours.
