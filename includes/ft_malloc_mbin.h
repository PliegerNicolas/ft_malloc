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

/** @brief Padded `mbin_t` structure size. @note Based on `sizeof(uniform_mbin_t)`. */
# define MBIN_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(mbin_t), MIN_ALIGNMENT_BOUNDARY)))

/** @brief Size of a TINY `mbin_t`, including metadata, padding and `uniform_mchunk_t`s.
 * @note Represents the number of bytes that should be requested through mmap() for a TINY `mbin_t`. */
# define TINY_MBIN_SIZE ((size_t)(ALIGN_UP(MBIN_METADATA_SIZE \
    + (TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN * TINY_MCHUNK_SIZE), PAGE_SIZE)))
/** @brief Size of a SMALL `mbin_t`, including metadata, padding and `uniform_mchunk_t`s.
 * @note Represents the number of bytes that should be requested through mmap() for a SMALL `mbin_t`. */
# define SMALL_MBIN_SIZE ((size_t)(ALIGN_UP(MBIN_METADATA_SIZE \
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

# define GET_MBIN_INITIAL_MCHUNK_PTR(mbin_ptr) \
    ((void *)((unsigned char *)(mbin_t *)(mbin_ptr) + MBIN_METADATA_SIZE))

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/** @brief Uniform `mbin_t` categories. @note Used with `uniform_mchunk_t`s. */
enum e_mbin_uniform_subcategory
{
    /** @brief Category for `uniform_mbin_t` structures managing tiny `uniform_mchunk_t` allocations. */
    MBIN_TINY,
    
    /** @brief Category for `uniform_mbin_t` structures managing small `uniform_mchunk_t` allocations. */
    MBIN_SMALL,

    /** @brief Number of supported `uniform_mbin_t` subcategories. */
    NUM_UNIFORM_MBIN_SUBCATEGORIES,
};

/** @brief Irregular `mbin_t` categories. @note Used with `irregular_mchunk_t`s. */
enum e_mbin_irregular_subcategory
{
    /** @brief Category for `irregular_mbin_t` structures managing large `irregular_mchunk_t` allocations. */
    MBIN_LARGE,

    /** @brief Number of supported `irregular_mbin_t` subcategories. */
    NUM_IRREGULAR_MBIN_SUBCATEGORIES,
};

/** @brief List of categories. */
enum e_mbin_categories
{
    UNIFORM,
    IRREGULAR,
    NUM_MBIN_CATEGORIES,
};

/* STRUCTURES */

// Could use an union, but it ould make it less clear and prone to errors.

typedef struct s_mbin
{
    /** @brief Union discriminator. */
    enum e_mbin_categories  category;
    /** @brief Initial `*_mchunk_t` defined inside this `mbin_t`.
     * @note Should be positionned just after this `mbin_t` in memory. */
    union {
        uniform_mchunk_t    *uniform_start;
        irregular_mchunk_t  *irregular_start;
    };

    /** @brief Available bytes for this `uniform_mbin_t`.
     * @note In other words, the size in bytes of the region provided by mmap(). */
    size_t                  size;

    /** @brief Next `mbin_t` of the doubly-linked-list. */
    struct s_mbin           *next;
    /** @brief Previous `mbin_t` of the doubly-linked-list. */
    struct s_mbin           *prev;
} mbin_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif
