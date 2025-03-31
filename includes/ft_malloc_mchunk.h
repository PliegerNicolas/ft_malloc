/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_chunk.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:24:43 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:24:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MCHUNK_H
# define FT_MALLOC_MCHUNK_H

/* *************************************************************************** */
/* *                          GENERAL DOCUMENTATION                          * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_global_macros.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

/* CONSTANTS */

/**
 * @brief How much data `TINY_MCHUNK` should be able to store in bytes.
 * 
 * @note Configurable arbitrary value.
 * */
# define TARGET_TINY_MCHUNK_MAX_DATA_SIZE ((size_t)64)
/**
 * @brief How much data `SMALL_MCHUNK` should be able to store in bytes.
 * 
 * @note Configurable arbitrary value.
 * */
# define TARGET_SMALL_MCHUNK_MAX_DATA_SIZE ((size_t)1024)

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Padded `uniform_mchunk_t` structure size. @note Based on `sizeof(uniform_mchunk_t)`. */
# define UNIFORM_MCHUNK_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(uniform_mchunk_t), MIN_ALIGNMENT_BOUNDARY)))
/** @brief Padded `irregular_mchunk_t` structure size. @note Based on `sizeof(irregular_mchunk_t)`. */
# define IRREGULAR_MCHUNK_METADATA_SIZE ((size_t)(ALIGN_UP(sizeof(irregular_mchunk_t), MIN_ALIGNMENT_BOUNDARY)))

/** @brief Padded tiny `uniform_mchunk_t` usable data size. @note Based on `TARGET_TINY_MCHUNK_MAX_DATA_SIZE`. */
# define TINY_MCHUNK_MAX_DATA_SIZE ((size_t)(ALIGN_UP(TARGET_TINY_MCHUNK_MAX_DATA_SIZE, MIN_ALIGNMENT_BOUNDARY)))
/** @brief Padded small `uniform_mchunk_t` usable data size. @note Based on `TARGET_SMALL_MCHUNK_MAX_DATA_SIZE`. */
# define SMALL_MCHUNK_MAX_DATA_SIZE ((size_t)(ALIGN_UP(TARGET_SMALL_MCHUNK_MAX_DATA_SIZE, MIN_ALIGNMENT_BOUNDARY)))

/** @brief Full padded size of a tiny `uniform_mchunk_t`, including metadata and data.
 * @note Based on `UNIFORM_MCHUNK_METADATA_SIZE` and `TINY_MCHUNK_MAX_DATA_SIZE`. */
# define TINY_MCHUNK_SIZE ((size_t)(UNIFORM_MCHUNK_METADATA_SIZE + TINY_MCHUNK_MAX_DATA_SIZE))
/** @brief Full padded size of a small `uniform_mchunk_t`, including metadata and data.
 * @note Based on `UNIFORM_MCHUNK_METADATA_SIZE` and `SMALL_MCHUNK_MAX_DATA_SIZE`. */
# define SMALL_MCHUNK_SIZE ((size_t)(UNIFORM_MCHUNK_METADATA_SIZE + SMALL_MCHUNK_MAX_DATA_SIZE))

/* FUNCTIONS */

/** @brief Padded large `irregular_mchunk_t` usable data size. */
# define LARGE_MCHUNK_MAX_DATA_SIZE(bytes_to_store) \
    ((size_t)(ALIGN_UP(bytes_to_store, MIN_ALIGNMENT_BOUNDARY)))

/** @brief Get current `irregular_mchunk_t` usable data size.
 * @note Might cause UB if *->size is smaller than `IRREGULAR_MCHUNK_METADATA_SIZE`. */
# define GET_IRREGULAR_MCHUNK_DATA_SIZE(irregular_mchunk_ptr) \
    ((size_t)((irregular_mchunk_t *)(irregular_mchunk_ptr))->size - IRREGULAR_MCHUNK_METADATA_SIZE)

/** @brief Get the data pointer of a `uniform_mchunk_t` pointer.
 * @note Based on `UNIFORM_MCHUNK_METADATA_SIZE`. */
# define GET_UNIFORM_MCHUNK_DATA_PTR(uniform_mchunk_ptr) \
    ((void *)((unsigned char *)((uniform_mchunk_t *)(uniform_mchunk_ptr)) + UNIFORM_MCHUNK_METADATA_SIZE))
/** @brief Get the data pointer of a `irregular_mchunk_t` pointer.
 * @note Based on `IRREGULAR_MCHUNK_METADATA_SIZE`. */
# define GET_IRREGULAR_MCHUNK_DATA_PTR(irregular_mchunk_ptr) \
    ((void *)((unsigned char *)((irregular_mchunk_t *)(irregular_mchunk_ptr)) + IRREGULAR_MCHUNK_METADATA_SIZE))

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/* ENUMERATORS */

/** @brief State of a `*_mchunk_t`. */
typedef enum e_mchunk_state {
    /** @brief `*_mchunk_t` is free for reuse or has never been used. */
    FREE,
    /** @brief `*_mchunk_t` is in use. */
    IN_USE,
} mchunk_state_t;

/* STRUCTURES */

/**
 * @brief Header for a memory chunk in a uniform-sized `mbin_t`.
 * 
 * Usable data is stored directly behind the header in memory. Don't forget about padding.
 * 
 * @note The size of the `uniform_mchunk_t`'s data is defined by its related `mbin_t` category.
 * For convenience, please use the provided macros (cf. header files).
 */
typedef struct s_uniform_mchunk
{
    /** @brief State of the `mchunk_t`. */
    mchunk_state_t  state;

    /** @brief Pointer to the closest next FREE `mchunk_t` of the current `mbin_t`. */
    struct s_uniform_mchunk *next_free_mchunk;
    /** @brief Pointer to the closest previous FREE `mchunk_t` of the current `mbin_t`. */
    struct s_uniform_mchunk *prev_free_mchunk;
}   uniform_mchunk_t;

/**
 * @brief Header for a memory chunk in a irregular-sized `mbin_t`.
 * 
 * Usable data is stored directly behind the header in memory. Don't forget about padding.

 * @note The size of the `irregular_mchunk_t`'s data is defined by its related `mbin_t` category.
 * For convenience, please use the provided macros (cf. header files).
 */
typedef struct s_irregular_mchunk
{
    /** @brief State of the `mchunk_t`. */
    mchunk_state_t  state;

    /** @brief Total space occupied by the `mchunk_t`.
     * Includes the `mchunk_t` header, any padding for alignment, and the space reserved for the usable data.
     * 
     * @note It is used for easy traversal and coalescing data in `mbin_t`s containing variable `*_mchunk_t` sizes.
     */
    size_t          size;
    /** @brief Total space occupied by the previous `mchunk_t` in memory.
     * Includes the `mchunk_t` header, any padding for alignment, and the space reserved for the usable data.
     * 
     * @note It is used for easy traversal and coalescing data in `mbin_t`s containing variable `*_mchunk_t` sizes.
     */
    size_t          prev_size;

    /** @brief Pointer to the closest next FREE `mchunk_t` of the current `mbin_t`. */
    struct s_irregular_mchunk *next_free_mchunk;
    /** @brief Pointer to the closest previous FREE `mchunk_t` of the current `mbin_t`. */
    struct s_irregular_mchunk *prev_free_mchunk;
}   irregular_mchunk_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif
