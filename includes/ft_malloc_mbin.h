/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_mbin.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:59:40 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:59:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MBIN_H
# define FT_MALLOC_MBIN_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_mchunk.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Minimum amount of allocations permitted per `uniform_mbin_t`.
 * @note Configurable arbitrary value. */
# define TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN ((size_t)(100))
/** @brief Minimum amount of allocations permitted per `irregular_mbin_t`.
 * @note Configurable arbitrary value. */
# define TARGET_MIN_ALLOCATIONS_PER_IRREGULAR_MBIN ((size_t)(1))

/** @brief Total `uniform_mbin_t` to create on heap initialization per category.
 * @note Configurable arbitrary value. */
# define TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY ((size_t)(3))

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Padded `uniform_mbin_t` structure size. @note Based on `sizeof(uniform_mbin_t)`. */
# define UNIFORM_MBIN_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(uniform_mbin_t), MIN_ALIGNMENT_BOUNDARY)))
/** @brief Padded `uniform_mbin_t` structure size. @note Based on `sizeof(irregular_mbin_t)`. */
# define IRREGULAR_MBIN_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(irregular_mbin_t), MIN_ALIGNMENT_BOUNDARY)))

/** @brief Size of a TINY `uniform_mbin_t`, including metadata, padding and `uniform_mchunk_t`s.
 * @note Represents the number of bytes that should be requested through mmap() for a TINY `uniform_mbin_t`. */
# define TINY_MBIN_SIZE ((size_t)(ALIGN_UP(UNIFORM_MBIN_METADATA_SIZE \
    + (TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN * TINY_MCHUNK_SIZE), PAGE_SIZE)))
/** @brief Size of a SMALL `uniform_mbin_t`, including metadata, padding and `uniform_mchunk_t`s.
 * @note Represents the number of bytes that should be requested through mmap() for a SMALL `uniform_mbin_t`. */
# define SMALL_MBIN_SIZE ((size_t)(ALIGN_UP(UNIFORM_MBIN_METADATA_SIZE \
    + (TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN * SMALL_MCHUNK_SIZE), PAGE_SIZE)))
    
/* FUNCTIONS */

/** @brief Size of a LARGE `irregular_mbin_t`, including metadata, padding and `irregular_mchunk_t`s.
 * @note Represents the number of bytes that should be requested through mmap()
 * for a LARGE `irregular_mbin_t`. If `bytes_to_store < IRREGULAR_MCHUNK_METADATA_SIZE`,
 * then 0 is forcefully returned. */
# define LARGE_MBIN_SIZE(bytes_to_store) \
    ((size_t)bytes_to_store >= IRREGULAR_MCHUNK_METADATA_SIZE \
        ? (ALIGN_UP(IRREGULAR_MCHUNK_METADATA_SIZE + \
            (TARGET_MIN_ALLOCATIONS_PER_IRREGULAR_MBIN * (size_t)(bytes_to_store)), PAGE_SIZE)) \
        : 0 \
    )

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/** @brief Uniform `mbin_t` categories. @note Used with `uniform_mchunk_t`s. */
enum e_mbin_uniform_category
{
    /** @brief Category for `uniform_mbin_t` structures managing tiny `uniform_mchunk_t` allocations. */
    MBIN_TINY,
    
    /** @brief Category for `uniform_mbin_t` structures managing small `uniform_mchunk_t` allocations. */
    MBIN_SMALL,

    /** @brief Number of supported `uniform_mbin_t` categories. */
    NUM_UNIFORM_MBIN_CATEGORIES,
};

/** @brief Irregular `mbin_t` categories. @note Used with `irregular_mchunk_t`s. */
enum e_mbin_irregular_category
{
    /** @brief Category for `irregular_mbin_t` structures managing large `irregular_mchunk_t` allocations. */
    MBIN_LARGE,

    /** @brief Number of supported `irregular_mbin_t` categories. */
    NUM_IRREGULAR_MBIN_CATEGORIES,
};

/* STRUCTURES */

/**
 * @brief A doubly-linked list of uniform-sized memory chunks, also called a memory bin.
 * This structure is used to manage memory bins that hold uniform-sized chunks.
 * 
 * @note Typically placed at the start of a memory region allocated via `mmap()`.
*/
typedef struct s_uniform_mbin
{
    /** @brief Initial `uniform_mchunk_t` defined inside this `uniform_mbin_t`.
     * @note Should be positionned just after this `uniform_mbin_t` in memory. */
    uniform_mchunk_t  *start;
    /** @brief Available bytes for this `uniform_mbin_t`.
     * @note In other words, the size in bytes of the region provided by mmap(). */
    size_t          size;

    /** @brief Next `uniform_mbin_t` of the doubly-linked-list. */
    struct s_mbin   *next;
    /** @brief Previous `uniform_mbin_t` of the doubly-linked-list. */
    struct s_mbin   *prev;
} uniform_mbin_t;

/**
 * @brief A doubly-linked list of irregularly sized memory chunks, also called a memory bin.
 * This structure is used to manage memory bins that hold irregularly sized chunks.
 * 
 * @note Typically placed at the start of a memory region allocated via `mmap()`.
*/
typedef struct s_irregular_mbin
{
    /** @brief Initial `irregular_mchunk_t` defined inside this `irregular_mbin_t`.
     * @note Should be positionned just after this `irregular_mbin_t` in memory. */
    irregular_mchunk_t    *start;
    /** @brief Available bytes for this `irregular_mbin_t`.
     * @note In other words, the size in bytes of the region provided by mmap(). */
    size_t              size;

    /** @brief Next `irregular_mbin_t` of the doubly-linked-list. */
    struct s_mbin       *next;
    /** @brief Previous `irregular_mbin_t` of the doubly-linked-list. */
    struct s_mbin       *prev;
} irregular_mbin_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif
