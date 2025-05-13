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

## **Intent of ft_malloc**
Our goal is to enhance **performance** by reducing the amount of **system calls**, albeit at the cost of **memory pre-allocation**, **memory fragmentation**. In other words: additional **overhead**.

Ideally **fragmentation** is kept minial.

### **Gains:**
- Fewer system calls through pre-allocation, enabling more efficient memory distribution via pointer arithmetic.
- Reduced fragmentation through optimized memory management techniques.
- Simplified memory management, making allocation easier to handle.

### **Losses:**
- Increased memory usage due to additional metadata for tracking and managing allocations.
- Extra memory overhead from pre-allocation.

With our **malloc** implementation, we aim to optimize memory allocation while balancing performance and efficiency.

## Internal structure

...

## libft_mini

I was not satisfied by my original [libft](https://github.com/PliegerNicolas/libft).
I decided to recreate one that answers my needs while using a more modern approach, now that I know C better.

## Usage

If you want to use this malloc implementation instead of the libc's one inside existing programs you have to:
- Prepend the path where `libft_malloc.so` is located in `LD_LIBRARY_PATH` environment variable. Ensure our *.so file is read first and has precedence.  
Please see how it's been done in my `tester`'s `Makefile`.
- Ensure the existing program only uses functions that are present in the header file of libc's malloc and ours.
