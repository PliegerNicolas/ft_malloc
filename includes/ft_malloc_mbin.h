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

/** @brief Minimum amount of allocations that can be handled per `UNIFORM` `mbin_t`.
 * @note Configurable arbitrary value. */
# define TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN ((size_t)(100))
/** @brief Minimum amount of allocations that can be handled per `NON_UNIFORM` `mbin_t`.
 * @note Configurable arbitrary value. */
# define TARGET_MIN_ALLOCATIONS_PER_NON_UNIFORM_MBIN ((size_t)(1))

/** @brief Total `UNIFORM` `mbin_t`s to create for each subcategory on heap initialization.
 * @note Configurable arbitrary value. */
# define TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY ((size_t)(3))

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* MBIN METADATA */

/** @brief Padded `mbin_t` structure size. @note Based on `sizeof(uniform_mbin_t)`. */
# define MBIN_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(mbin_t), MIN_ALIGNMENT_BOUNDARY)))

/* MBIN SIZES */

/** @brief Total `PAGE` aligned size in bytes of a `TINY_MBIN` (metadata and data included).
 * @note This value should be passed to mmap(). */
# define TINY_MBIN_SIZE ((size_t)(ALIGN_UP(MBIN_METADATA_SIZE + (TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN * TINY_MCHUNK_SIZE), PAGE_SIZE)))
/** @brief Total `PAGE` aligned size in bytes of a `SMALL_MBIN` (metadata and data included).
 * @note This value should be passed to mmap(). */
# define SMALL_MBIN_SIZE ((size_t)(ALIGN_UP(MBIN_METADATA_SIZE + (TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN * SMALL_MCHUNK_SIZE), PAGE_SIZE)))
/** @brief Total `PAGE` aligned size in bytes of a `LARGE_MBIN` (metadata and data included).
 * @param mchunk_data_size (size_t) Number of bytes the `mbin_t`s is expected to hold per `mchunk_t`.
 * @note This value should be passed to mmap(). */
# define LARGE_MBIN_SIZE(mchunk_data_size) \
    ((size_t)(ALIGN_UP(MBIN_METADATA_SIZE + \
        (TARGET_MIN_ALLOCATIONS_PER_NON_UNIFORM_MBIN * LARGE_MCHUNK_SIZE(mchunk_data_size)), PAGE_SIZE)))
    
/* MBIN MCHUNKs */

/** @return The address to the first `*mchunk_ptr` in the given `mbin_t`. */
# define MBIN_INITIAL_MCHUNK_PTR(mbin_ptr) \
    ((mchunk_t *)((unsigned char *)((mbin_t *)mbin_ptr) + MBIN_METADATA_SIZE))

/** @return The size the `mbin_t` dedicates to it's `mchunk_t`s.
 * @note In other words. The size of it's first `mchunk_t`. */
# define MBIN_INITIAL_MCHUNK_SIZE(mbin_ptr) \
    ((size_t)((mbin_t *)mbin_ptr->size - MBIN_METADATA_SIZE))

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/* ENUMS */

/** @brief `mbin_t` categories.
 * @param MBIN_UNIFORM stores it's `mchunk_t`s in a uniform manner. Evenly space and of constant size.
 * @param MBIN_UNIFORM stores it's `mchunk_t`s in a non-uniform manner. Size is determined on the fly.
 */
typedef enum e_mbin_category
{
    MBIN_UNIFORM,
    MBIN_NON_UNIFORM,
    NUM_MBIN_CATEGORIES,
} mbin_category_t;

/** @brief */
typedef enum e_mbin_subcategory
{
    MBIN_TINY,
    MBIN_SMALL,
    MBIN_LARGE,
    NUM_MBIN_SUBCATEGORIES,
} mbin_subcategory_t;

/* STRUCTURES */

/**
 * @brief Header for a `marena_t` memory bin.
 * Usable data is stored directly behind the header in memory (`mchunk_t` *start).
 * Don't forget about padding.

 * @note For convenience, please use the provided macros (cf. header files).
 */
typedef struct s_mbin
{
    /** @brief Pointer to the first `mchunk_t` held by this `mbin_t`. */
    mchunk_t        *start;

    /** @brief Aligned size of current `mbin_t`. Metadata and data included.
     * @note The size requested to mmap(). */
    size_t          size;

    /** @brief Next `mbin_t` of this doubly-linked list.
     * @note NULL if current. */
    struct s_mbin   *next;
    /** @brief Previous `mbin_t` of this doubly-linked list.
     * @note NULL if current. */
    struct s_mbin   *prev;
} mbin_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* mappings */

size_t              get_mbin_size(size_t requested_bytes);
mbin_category_t     get_mbin_category(mbin_subcategory_t subcategory);
mbin_subcategory_t  get_mbin_subcategory(size_t mchunk_data_size);
size_t              get_mbin_subcategory_mchunk_size(mbin_subcategory_t subcategory, size_t requested_bytes);
size_t              get_mbin_subcategory_mchunk_data_size(mbin_subcategory_t subcategory, size_t requested_bytes);
char                *get_mbin_category_name(size_t mbin_size);
char                *get_mbin_subcategory_name(size_t mbin_size);

mbin_t              *mmap_mbin(size_t mmap_size);
mbin_t              *new_mbin(size_t requested_data_size);
void                mchunkify_mbin(mchunk_t **initial_mchunk, size_t target_mchunk_size);

void                prepend_mbin(mbin_t **mbin, mbin_t *new_mbin);
void                append_mbin(mbin_t **mbin, mbin_t *new_mbin);

size_t              show_mbin(mbin_t **mbin, int fd);
void                clear_mbin(mbin_t **mbin);

#endif
