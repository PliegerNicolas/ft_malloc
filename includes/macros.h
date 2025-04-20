/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 01:40:06 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 01:40:06 by nicolas          ###   ########.fr       */
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

/* SYSTEM */

/**
 * @brief General use-case memory memory alignment boundary in bytes.
 * 
 * Alignment improves performance by adhering to architecture-specific requirements.
 * Padding can be used to ensure stored memory in set on a memory alignment boundary.
 * 
 * @note Should be a multiple of 2. Consider frequently used SIMD operations (SSE, AVX...).
 */
# define ALIGNMENT_BOUNDARY (size_t)16

/* MCHUNK */

/**
 * @brief Maximum number of bytes that can be stored in `mchunk_t` within a TINY `marena_t`.
 * @note This value is aligned to the selected `ALIGNMENT_BOUNDARY` for performance optimization. Use `MCHUNK_TINY_MAX_DATA_SIZE`.
 */
# define TARGET_MCHUNK_TINY_MAX_DATA_SIZE (size_t)64

/**
 * @brief Maximum number of bytes that can be stored in `mchunk_t` within a SMALL `marena_t`.
 * @note This value is aligned to the selected `ALIGNMENT_BOUNDARY` for performance optimization. Use `MCHUNK_SMALL_MAX_DATA_SIZE`.
 */
# define TARGET_MCHUNK_SMALL_MAX_DATA_SIZE (size_t)512

/**
 * @brief Minimum `mchunk_t`s per bounded `mregion_t`.
 * @note This greatly affects bounded `marena_t` sizes.
 */
# define MIN_MCHUNKS_PER_BOUNDED_MREGION (size_t)124

/**
 * @brief How much mregions should be preallocated on `ft_malloc` initialization.
*/
# define NUM_INITIAL_BOUNDED_MREGIONS (size_t)3

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* SYSTEM */

/**
 * @brief System's page size in bytes.
 * @note Take into account that this declaration Can fail and be set to (size_t)-1.
 */
# define PAGE_SIZE ((size_t)sysconf(_SC_PAGE_SIZE))

/**
 * @brief Rounds a arithmetic and bitwise operations value to a given alignment boundary.
 * @param value Any type supporting arithmetic and bitwise operations (`int`, `size_t`, `uintptr_t`...).
 * @param align The alignment boundary. Should be a power of 2.
 * @returns {typeof value}
 */
# define ALIGN_UP(value, align) (((value) + (align - 1)) & ~(align - 1))

/* MCHUNK */

/** @brief Size of a `mchunk_t` rounded up to the nearest `ALIGNMENT_BOUNDARY` in bytes. */
# define MCHUNK_HEADER_PADDED_SIZE ((size_t)ALIGN_UP(sizeof(mchunk_t), ALIGNMENT_BOUNDARY))

/** @brief Maximum number of bytes that can be stored in `mchunk_t` within a TINY `marena_t`. */
# define MCHUNK_TINY_MAX_DATA_SIZE ((size_t)ALIGN_UP(TARGET_MCHUNK_TINY_MAX_DATA_SIZE, ALIGNMENT_BOUNDARY))
/** @brief Maximum number of bytes that can be stored in `mchunk_t` within a SMALL `marena_t`. */
# define MCHUNK_SMALL_MAX_DATA_SIZE ((size_t)ALIGN_UP(TARGET_MCHUNK_SMALL_MAX_DATA_SIZE, ALIGNMENT_BOUNDARY))

/** @returns {void*} Pointer to the start of the `mchunk_t`'s data region. */
# define GET_MCHUNK_DATA_PTR(mchunk_ptr) ((void *)((unsigned char *)(mchunk_t *)mchunk_ptr + MCHUNK_HEADER_PADDED_SIZE))

/** @brief {size_t} Get size in bytes of current `mchunk_t`, including metadata, memory alignment padding and stored data. */
# define GET_MCHUNK_PADDED_SIZE(mchunk_ptr) ((size_t)(MCHUNK_HEADER_PADDED_SIZE + ALIGN_UP(((mchunk_t *)mchunk_ptr)->allocation_size, ALIGNMENT_BOUNDARY)))
/** @brief {size_t} Get size in bytes of previous `mchunk_t`, including metadata, memory alignment padding and stored data. */
# define GET_PREV_MCHUNK_PADDED_SIZE(mchunk_ptr) ((size_t)(MCHUNK_HEADER_PADDED_SIZE + ALIGN_UP(((mchunk_t *)mchunk_ptr)->prev_allocation_size, ALIGNMENT_BOUNDARY)))

/**
 * @brief {mchunk_t*} Get pointer to next memory adjacent `mchunk_t*`.
 * @warning It doesn't ensure the pointer is in a valid memory space.
 * @note Returns NULL if `mchunk_ptr`->allocated_size == 0.
 */
# define GET_NEXT_MCHUNK_PTR(mchunk_ptr) ( \
	(((mchunk_t *)mchunk_ptr)->allocation_size != 0) \
		? (mchunk_t *)((unsigned char *)mchunk_ptr + GET_MCHUNK_PADDED_SIZE(mchunk_ptr)) \
		: (mchunk_t *)NULL \
)
/**
 * @brief {mchunk_t*} Get pointer to previous memory adjacent `mchunk_t*`.
 * @warning It doesn't ensure the pointer is in a valid memory space.
 * @note Returns NULL if `mchunk_ptr`->prev_allocated_size == 0.
 */
# define GET_PREV_MCHUNK_PTR(mchunk_ptr) ( \
	(((mchunk_t *)(mchunk_ptr))->prev_allocation_size != 0) \
		? (mchunk_t *)((unsigned char *)(mchunk_ptr) - GET_PREV_MCHUNK_PADDED_SIZE(mchunk_ptr)) \
		: NULL \
)

/* MREGION */

/** @brief Size of a `mregion_t` rounded up to the nearest `PAGE_SIZE` in bytes. */
# define MREGION_HEADER_PADDED_SIZE ((size_t)ALIGN_UP(sizeof(mregion_t), ALIGNMENT_BOUNDARY))

/** @returns {mchunk_t*} Pointer to the base/initial `mchunk_t`, located directly after this `mregion_t` in memory. */
# define GET_MREGION_MBIN_PTR(mregion_ptr) ((mchunk_t *)((unsigned char *)mregion_ptr + MREGION_HEADER_PADDED_SIZE))

/* Other */

/**
 * @brief Represents a successful operation. It also is an invalid memory address.
 * @note Used with `status`.
*/
# define STATUS_SUCCESS ((status_t)-1)
/**
 * @brief Represents a failed operation. It also is an invalid memory address.
 * @note Used with `status`.
*/
# define STATUS_FAILURE ((status_t)-2)

#endif // MACROS_H