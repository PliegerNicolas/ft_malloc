/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 12:39:24 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 12:39:24 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* For size_t. */
# include <stddef.h>

/* For sysconf() */
#include <unistd.h>

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/* Forward declarations */

typedef struct  s_mchunk mchunk_t;
typedef struct  s_mregion mregion_t;
typedef struct  s_marena marena_t;
typedef struct  s_heap_info heap_info_t;

/* Models */

/** @brief A (void*) alias. Used when the intention is to divulgue an operation state.  */
typedef void*   status_t;

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

/* DEBUG */

/** @brief Adds some extra information on usage. */
# ifndef MALLOC_DEBUG
#  define MALLOC_DEBUG 0
# endif

/* SYSTEM */

/** @brief Desired general use-case memory alignment boundary in bytes.
 * 
 * Alignment improves performance by adhering to architecture specific requirements.
 * Consider SIMD operations (SSE, AVX...).
 * 
 * @note Will be rounded up to the nearest multiple of 2. */
# define DESIRED_ALIGNMENT_BOUNDARY (size_t)16

/* MCHUNK */

/** @brief Desired maximum allocation_size per TINY `mchunk_t`.
 * @note Will be rounded up to `ALIGNMENT_BOUNDARY`. */
# define DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE (size_t)128
/** @brief Maximum allocation_size per TINY `mchunk_t`.
 * @note Will be rounded up to `ALIGNMENT_BOUNDARY`. */
# define DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE (size_t)1024

/* MREGION */

/** @brief Desired number of `mchunk_t` a bound `mregion_t` should hold, at least.
 * @note Clamped to a minimum of 100. */
# define DESIRED_MCHUNKS_PER_BOUND_MREGION (size_t)124

/** @brief Desired number of `mchunk_t` an unbound `mregion_t` should hold, at least.
 * @note Clamped to a minimum of 1. */
# define DESIRED_MCHUNKS_PER_UNBOUND_MREGION (size_t)1

/* MARENA */

/** @brief Desired number of initialised `mregion_t` per bound category. */
# define DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE (size_t)1

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* SYSTEM / PLATEFORM */

/** @returns A boolean expressing if the value is a power of 2. */
# define IS_POW_2(value) ((bool)((value) && !(value & (value - 1))))

/** @brief Align `value` downwards to next power of 2. */
# define ALIGN_DOWN_POW2(value) ((size_t)(value) <= 1 ? (size_t)1 : ((size_t)1 << (sizeof(size_t) * CHAR_BIT - ft_clz_size_t((size_t)value) - 1)))
/** @brief Align `value` downwards to next power of 2. */
# define ALIGN_UP_POW2(value) ((size_t)(value) <= 1 ? (size_t)1 : ((size_t)1 << (sizeof(size_t) * CHAR_BIT - ft_clz_size_t((size_t)(value) - 1))))

/** @brief Aligns `value` upwards to the nearest multiple of `align`. */
# define ALIGN_UP(value, align) (((value) + (align - 1)) & ~(align - 1))
/** @brief Aligns `value` downwards to the nearest multiple of `align`. */
# define ALIGN_DOWN(value, align) ((value) & ~((align) - 1))

/** @returns The highest value between `value` and `min` */
# define CLAMP_MIN(value, min) (((value) < (min)) ? (min) : (value))
/** @returns The smallest value between `value` and `max` */
# define CLAMP_MAX(value, max) (((value) > (max)) ? (max) : (value))

/** @brief Checks if a value or pointer is aligned given an alignment boundary. */
# define IS_ALIGNED(val, align) ((bool)(((uintptr_t)(val) % (uintptr_t)(align)) == 0))

/** @brief General use-case memory alignment boundary in bytes. */
# define ALIGNMENT_BOUNDARY (size_t)(ALIGN_UP_POW2(DESIRED_ALIGNMENT_BOUNDARY))

# ifndef PAGE_SIZE
#  if defined(__linux__)
/** @brief System's page size in bytes. */
#   define PAGE_SIZE (size_t)(sysconf(_SC_PAGESIZE))
#  elif defined(__APPLE__)
/** @brief System's page size in bytes. */
#   define PAGE_SIZE (size_t)(getpagesize())
#  else
#   error "Unsupported operating system."
#  endif
# endif

/* MREGION */

/** @brief Number of `mchunk_t` a bound `mregion_t` can hold, at least. */
# define MCHUNKS_PER_BOUND_MREGION (CLAMP_MIN(DESIRED_MCHUNKS_PER_BOUND_MREGION, 100))
/** @brief Number of `mchunk_t` an unbound `mregion_t` can hold, at least. */
# define MCHUNKS_PER_UNBOUND_MREGION (CLAMP_MIN(DESIRED_MCHUNKS_PER_UNBOUND_MREGION, 1))

/** @brief Number of initialised `mregion_t` per bound category. */
# define INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE (CLAMP_MIN(DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, 0))

/** @brief Size of a `mregion_t` header. */
# define MREGION_HEADER_SIZE (size_t)ALIGN_UP(sizeof(mregion_t), ALIGNMENT_BOUNDARY)

/** @brief Size of a tiny `mregion_t`. */
# define TINY_MREGION_SIZE ALIGN_UP((MREGION_HEADER_SIZE + (MCHUNKS_PER_BOUND_MREGION * GET_MCHUNK_SIZE(TINY_MCHUNK_MAX_ALLOCATION_SIZE))), PAGE_SIZE)
/** @brief Size of a small `mregion_t`. */
# define SMALL_MREGION_SIZE ALIGN_UP((MREGION_HEADER_SIZE + (MCHUNKS_PER_BOUND_MREGION * GET_MCHUNK_SIZE(SMALL_MCHUNK_MAX_ALLOCATION_SIZE))), PAGE_SIZE)
/** @brief Size of a large `mregion_t`, given a target `allocation_size`. */
# define LARGE_MREGION_SIZE(allocation_size) ALIGN_UP((MREGION_HEADER_SIZE + (MCHUNKS_PER_UNBOUND_MREGION * GET_MCHUNK_SIZE(allocation_size))), PAGE_SIZE)

/** @brief Calculate pointer to the first `mchunk_t` of given `mregion_t`. */
# define GET_MREGION_FIRST_MCHUNK(mregion_ptr) ((mchunk_t *)((unsigned char*)(mregion_ptr) + MREGION_HEADER_SIZE))

/** @returns True if the allocation_size fits within a bound mregion (cf. `bound_mregion_type_t`). */
# define IS_BOUND_MREGION(allocation_size) ((bool)((size_t)allocation_size <= SMALL_MCHUNK_MAX_ALLOCATION_SIZE))

/* MCHUNK */

/** @brief Size of a `mchunk_t` header. */
# define MCHUNK_HEADER_SIZE (size_t)(ALIGN_UP(sizeof(mchunk_t), ALIGNMENT_BOUNDARY))

/** @brief Calculates size of a `mchunk_t` given a desired `allocation_size`. */
# define GET_MCHUNK_SIZE(allocation_size) ((size_t)(MCHUNK_HEADER_SIZE + ALIGN_UP((size_t)(allocation_size), ALIGNMENT_BOUNDARY)))

/** @brief Calculates pointer to the data referenced by the `mchunk_t`. */
# define GET_MCHUNK_DATA_PTR(mchunk_ptr) ((void*)((unsigned char*)(mchunk_ptr) + MCHUNK_HEADER_SIZE))
/** @brief Given a `void` pointer, calculates the address of the supposed affiliated `mchunk_t`. */
# define GET_MCHUNK_PTR(data_ptr) ((mchunk_t *)((unsigned char *)data_ptr - MCHUNK_HEADER_SIZE))

/** @brief Maximum allocation_size per TINY `mchunk_t`. */
# define TINY_MCHUNK_MAX_ALLOCATION_SIZE (size_t)(ALIGN_UP(DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE, ALIGNMENT_BOUNDARY))
/** @brief Maximum allocation_size per TINY `mchunk_t`. */
# define SMALL_MCHUNK_MAX_ALLOCATION_SIZE (size_t)(ALIGN_UP(DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE, ALIGNMENT_BOUNDARY))

/** @brief Minimum allocation_size per TINY `mchunk_t`. */
# define TINY_MCHUNK_MIN_ALLOCATION_SIZE (size_t)(0)
/** @brief Minimum allocation_size per SMALL `mchunk_t`. */
# define SMALL_MCHUNK_MIN_ALLOCATION_SIZE (size_t)(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1)
/** @brief Minimum allocation_size per LARGE `mchunk_t`. */
# define LARGE_MCHUNK_MIN_ALLOCATION_SIZE (size_t)(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1)

/** @returns Calculates pointer to the next `mchunk_t` in memory. */
# define GET_NEXT_MCHUNK(mchunk_ptr) ((mchunk_t*)((unsigned char*)(mchunk_ptr) + GET_MCHUNK_SIZE(((mchunk_t*)(mchunk_ptr))->allocation_size)))
/** @returns Calculates pointer to the previous `mchunk_t` in memory. */
# define GET_PREV_MCHUNK(mchunk_ptr) ((mchunk_t*)((unsigned char*)(mchunk_ptr) - GET_MCHUNK_SIZE(((mchunk_t*)(mchunk_ptr))->prev_allocation_size)))

/* Other */

/** @brief Page aligned value closest to (size_t)-1 */
# define PAGE_ALIGNED_SIZE_MAX (size_t)ALIGN_DOWN(SIZE_MAX, PAGE_SIZE)
/** @brief Maximum allocation_size */
# define MAX_ALLOCATION_SIZE (size_t)(ALIGN_DOWN_POW2((PAGE_ALIGNED_SIZE_MAX - MREGION_HEADER_SIZE) / (MCHUNKS_PER_UNBOUND_MREGION * MREGION_HEADER_SIZE)))

/** @brief Represents a successful operation. It's also an invalid memory address.
 * @note Used with `status_t`. */
# define STATUS_SUCCESS ((status_t)-1)
/** @brief Represents a failed operation or a misused function. It's also an invalid memory address.
 * @note Used with `status_t`. */
# define STATUS_FAILURE ((status_t)-2)

#endif // MACROS_H
