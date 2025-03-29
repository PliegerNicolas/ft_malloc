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
- **`mbin_t`:** Doubly-linked-list of memory region allocated by `mmap()`, their `mchunk_t`s and some metadata.  
- **`arena_t`**: Contains a arbitrarly defined fixed-size of `mbin_t` sizes and their configuration (kind of `mchunk_t` data to stored and etc.).  
- **`heap_t`**: Root structure containing data about the portion(s) of the heap we're using with our ft_malloc implementation.  

A more precise explanation of each of these structures can be found inside their relative header files.