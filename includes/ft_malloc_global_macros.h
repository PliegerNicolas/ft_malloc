/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:24:07 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:24:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MACROS_H
# define FT_MALLOC_MACROS_H

/* *************************************************************************** */
/* *                          GENERAL DOCUMENTATION                          * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* For size_t. */
# include <stddef.h>

/* For MMAP related constants. */
// Include the necessary GNU extensions (https://github.com/microsoft/vscode-cpptools/issues/4268) for MAP_ANONYMOUS.
#define _GNU_SOURCE
#include <sys/mman.h>

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Minimum memory alignment boundary (in bytes).
 * Should be a multiple of 2. 16 is recommended to accomodate SIMD operations.
 * 
 * @note Configurable arbitrary value.
*/
# define MIN_ALIGNMENT_BOUNDARY ((size_t) 16)

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief System page size in bytes (typically aligned to a multiple of 2). */
# define PAGE_SIZE ((size_t)(sysconf(_SC_PAGE_SIZE)))

// # if defined(_SC_PAGE_SIZE)
// #  define PAGE_SIZE ((size_t)(sysconf(_SC_PAGE_SIZE)))
// # elif defined(_SC_PAGESIZE)
// #  define PAGE_SIZE ((size_t)(sysconf(_SC_PAGESIZE)))
// # elif defined
// #  define PAGE_SIZE ((size_t)getpagesize())
// # endif

/**
 * @brief Memory protections for mmap().
 * 
 * Readable as the process should be able to read from it.
 * Writable as the process should be able to write to it.
*/
# define MMAP_PROTECTIONS (PROT_READ | PROT_WRITE)

/**
 * @brief mmap() flags.
 * 
 * Private as it should only accessible by the current process and it's threads.
 * Anonymous as we the memory allocations are temporary and only used at runtime.
*/
# define MMAP_FLAGS (MAP_PRIVATE | MAP_ANONYMOUS)

/* FUNCTIONS */

/** 
 * @brief Rounds `value` up to the nearest multiple of `align`. 
 * 
 * @param value The value to align (size_t).
 * @param align Alignment boundary. Should be a power of 2 (size_t).
 * @return Aligned value (size_t).
*/
#define ALIGN_UP(value, align) \
    ((size_t)(value) + ((align) - 1)) & ~((align) - 1)

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/** @brief A pointer to indicate failure. */
# define FAILURE ((void *)-1)
/** @brief A pointer to indicate success. */
# define SUCCESS ((void *)1)
/** @brief A pointer indicating execution status.
 * @note To be used with `SUCCESS` and `FAILURE`.
*/
typedef void    *status_t;

#endif
