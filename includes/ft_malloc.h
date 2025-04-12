/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-27 09:46:49 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-27 09:46:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

/* *************************************************************************** */
/* *                          GENERAL DOCUMENTATION                          * */
/* *************************************************************************** */

/*
 * Retrieving memory from the operating system using mmap has disadvantages:
 * - It is page-based, making it inefficient for small memory allocations.
 * - Frequent use can be slow due to system call overhead.
 *
 * Retrieving memory from the operating system using (s)brk has disadvantages:
 * - It operates in a contiguous manner, making arbitrary memory deallocation difficult, 
 *   which can lead to inefficient memory usage and long-term fragmentation.
 * - It has a higher complexity in usage.
 *
 * Our objective with ft_malloc is to minimize memory fragmentation 
 * and improve performance, albeit at the cost of memory overhead.
 *
 * **Gains:**
 * - Fewer system calls through pre-allocation, enabling efficient pointer arithmetic.
 * - Reduced fragmentation through optimized memory management.
 * - Partial abstraction of memory management for easier allocation handling.
 *
 * **Losses:**
 * - Increased memory usage due to metadata for memory management and tracking.
 * - Additional memory overhead from pre-allocation.
*/

/*
* For ft_malloc, our data is stored relative to the following hierarchy:
* - nº1: t_heap => contains all the arenas and some metadata. It's the root structure.
* - nº2: t_arena => contains multiple "t_mbins" separated by type/category and some metadata.
* - nº2: t_mbins => contains memory regions allocated by mmap(), splitted into usable chunks and some metadata.
* - nº3: t_mchunk => contains the actual stored user's data and it's metadata.
*/

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_heap.h"

/* libft_mini */
# include "libft_mini.h"

/* For NULL and size_t. */
# include <stddef.h>

/* For mmap and munmap (man 2 mmap). */
# include <sys/mman.h>

/* For struct rlimit and getrlimit().  */
#include <sys/resource.h>

/* For getrlimit (man 2 getrlimit). */
# include <sys/time.h>

/* For all functions available in the library. */
# include <pthread.h>

/* Present in libft... */
# include <unistd.h>

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Global variable */
extern heap_t   gheap;

/* Mandatory functions */

void                *malloc(size_t size);
void                *realloc(void *ptr, size_t size);
void                free(void *ptr);
void                show_alloc_mem();

#endif
