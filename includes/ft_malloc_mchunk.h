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
 * @brief How much data a `TINY_MCHUNK` should be able to hold in bytes.
 * @note Configurable arbitrary value.
*/
# define TARGET_TINY_MCHUNK_DATA_SIZE \
    ((size_t)64)

/**
 * @brief How much data a `SMALL_MCHUNK` should be able to hold in bytes.
 * @note Configurable arbitrary value.
*/
# define TARGET_SMALL_MCHUNK_DATA_SIZE \
    ((size_t)1024)

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* MCHUNK METADATA */

/** @brief Aligned `mchunk_t` structure size in bytes. */
#define MCHUNK_METADATA_SIZE \
    ((size_t)(ALIGN_UP(sizeof(mchunk_t), MIN_ALIGNMENT_BOUNDARY)))

/* MCHUNK DATA */

/** @brief How much data a `TINY` `mchunk_t` can hold, in bytes. */
#define TINY_MCHUNK_DATA_SIZE \
    ((size_t)ALIGN_UP(TARGET_TINY_MCHUNK_DATA_SIZE,MIN_ALIGNMENT_BOUNDARY))
/** @brief How much data a `SMALL` `mchunk_t` can hold, in bytes. */
#define SMALL_MCHUNK_DATA_SIZE \
    ((size_t)ALIGN_UP(TARGET_SMALL_MCHUNK_DATA_SIZE,MIN_ALIGNMENT_BOUNDARY))
/** @brief  How much data a `LARGE` `mchunk_t` can hold, in bytes. */
#define LARGE_MCHUNK_DATA_SIZE(bytes) \
    ((size_t)ALIGN_UP((size_t)bytes, MIN_ALIGNMENT_BOUNDARY))

/** @return A pointer to the data held by a `mchunk_t`. */
# define GET_MCHUNK_DATA_PTR(mchunk_ptr) \
    ((void *)(unsigned char *)(mchunk_t *)mchunk_ptr + MCHUNK_METADATA_SIZE)
/** @return A pointer to the data held by a `mchunk_t`. */
# define GET_MCHUNK_DATA_SIZE(mchunk_ptr) \
    ((size_t)((mchunk_t *)mchunk_ptr)->size - MCHUNK_METADATA_SIZE)

/* MCHUNK */

/** @brief Aligned size of `TINY` `mchunk_t`: metadata + data.*/
# define TINY_MCHUNK_SIZE \
    ((size_t)(MCHUNK_METADATA_SIZE + TINY_MCHUNK_DATA_SIZE))
/** @brief Aligned size of `SMALL` `mchunk_t`: metadata + data.*/
# define SMALL_MCHUNK_SIZE \
    ((size_t)(MCHUNK_METADATA_SIZE + SMALL_MCHUNK_DATA_SIZE))
/** @brief Aligned size of `LARGE` `mchunk_t`: metadata + data.*/
# define LARGE_MCHUNK_SIZE(bytes) \
    ((size_t)(MCHUNK_METADATA_SIZE + LARGE_MCHUNK_DATA_SIZE((size_t)bytes)))

/** @return Get the next `mchunk_t*` in memory. */
# define GET_NEXT_MCHUNK_PTR(mchunk_ptr) \
    ((mchunk_t *)((unsigned char *)((mchunk_t *)mchunk_ptr) + ((mchunk_t*)mchunk_ptr)->size))
/** @return Get the previous `mchunk_t*` in memory. */
# define GET_PREVIOUS_MCHUNK_PTR(mchunk_ptr) \
    ((mchunk_t *)((unsigned char *)((mchunk_t *)mchunk_ptr) - ((mchunk_t*)mchunk_ptr)->prev_size))

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/* ENUMERATORS */

typedef enum e_mchunk_state
{
    FREE,
    IN_USE,
    NUM_MCHUNK_STATES,
} mchunk_state_t;

/* STRUCTURES */

/**
 * @brief Header for a `mbin_t` memory chunk.
 * Usable data is stored directly behind the header in memory. Don't forget about padding.

 * @note The `mchunk_t` data size is defined by its related `mbin_t` category.
 * For convenience, please use the provided macros (cf. header files).
 */
typedef struct s_mchunk
{
    /** @brief State of the mchunk: FREE, IN_USE */
    mchunk_state_t  state;

    /** @brief Padded size of current `mchunk_t`: metadata + size.
     * @note 0 if not found. Not useful in `UNIFORM` `mchunk_t`s. */
    size_t          size;
    /** @brief Padded size of previous `mchunk_t`: metadata + size.
     * @note 0 if not found. Not useful in `UNIFORM` `mchunk_t`s. */
    size_t          prev_size;
    /** @brief User requested size.
     * @note The actual size of the data requested by the user. */
    size_t          requested_size;

    /** @brief Pointer to the closest previous FREE `mchunk_t` of the current `mbin_t`.
     * @note NULL if current. */
    struct s_mchunk *next_free_mchunk;
    /** @brief Pointer to the closest previous FREE `mchunk_t` of the current `mbin_t`.
     * @note NULL if current. */
    struct s_mchunk *prev_free_mchunk;
} mchunk_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* mchunk_t */

mchunk_t    *mchunk_create_next(mchunk_t **mchunk, size_t target_mchunk_size);

size_t      mchunks_inspect(mchunk_t **initial_mchunk, int fd);

/* inference */

size_t      mchunk_infer_size_by_storage_size(size_t requested_bytes);
size_t      mchunk_infer_data_size(mchunk_t *mchunk);

#endif
