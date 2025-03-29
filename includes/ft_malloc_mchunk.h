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
 * @brief Configurable arbitrary value for tiny `mchunk_t` maximum size.
 * It should have enough space to store `MCHUNK_ALIGNED_SIZE`.
*/
# define TARGET_TINY_CHUNK_SIZE ((size_t)(256))
/**
 * @brief Configurable arbitrary value for small `mchunk_t` maximum size.
 * It should have enough space to store `MCHUNK_ALIGNED_SIZE`.
*/
# define TARGET_SMALL_CHUNK_SIZE ((size_t)(1024))

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Size of `mchunk_t` aligned to MIN_ALIGNMENT_BOUNDARY. */
# define MCHUNK_ALIGNED_SIZE ((size_t)(ALIGN_UP(sizeof(mchunk_t), MIN_ALIGNMENT_BOUNDARY)))

/** @brief Size dedicated to a tiny `mchunk_t`, including the struct itself and the held data. */
# define TINY_MCHUNK_SIZE ((size_t)(ALIGN_UP(TARGET_TINY_CHUNK_SIZE, MIN_ALIGNMENT_BOUNDARY)))
/** @brief Size dedicated to a small `mchunk_t`, including the struct itself and the held data. */
# define SMALL_MCHUNK_SIZE ((size_t)(ALIGN_UP(TARGET_SMALL_CHUNK_SIZE, MIN_ALIGNMENT_BOUNDARY)))

/** @brief Maximum data storable in a tiny `mchunk_t`, excluding the struct itself. */
# define MAX_TINY_MCHUNK_DATA_SIZE ((size_t)(TINY_MCHUNK_SIZE - MCHUNK_ALIGNED_SIZE))
/** @brief Maximum data storable in a small `mchunk_t`, excluding the struct itself. */
# define MAX_SMALL_MCHUNK_DATA_SIZE ((size_t)(SMALL_MCHUNK_SIZE - MCHUNK_ALIGNED_SIZE))

/* FUNCTIONS */

/**
 * @brief Get the size of the data stored after the current `mchunk_t` in bytes.
 * 
 * If MCHUNK_ALIGNED_SIZE < mchunk_ptr->size, then 0 is forcefully returned. 
 * 
 * @param mchunk_ptr (mchunk_t *) Pointer to a given `mchunk_t`.
 * @return (size_t) Size in bytes of stored data.
*/
#define GET_MCHUNK_DATA_SIZE(mchunk_ptr) \
    ((size_t)( \
        ((mchunk_t *)(mchunk_ptr))->size > MCHUNK_ALIGNED_SIZE \
        ? ((mchunk_t *)(mchunk_ptr))->size - MCHUNK_ALIGNED_SIZE \
        : 0 \
    ))

/**
 * @brief Get pointer to the `mchunk_t`s data.
 * 
 * @param mchunk_ptr (mchunk_t *) Pointer to a given `mchunk_t`.
 * @return (void *) Pointer to the stored data.
*/
# define GET_MCHUNK_DATA_PTR(mchunk_ptr) \
    ((void *)((char *)mchunk_ptr + MCHUNK_ALIGNED_SIZE))

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @enum e_mchunk_state
 * @brief Enumeration representing the supported `mchunk_t` states.
*/
enum e_mchunk_state {
    /** @brief Chunk is marked as free (either freed or never used). */
    FREE,
    
    /** @brief Chunk is marked as in use. */
    IN_USE,
};

/**
 * @struct s_mchunk
 * @brief Metadata that provides information about the stored user data.
 *
 * The user data is stored immediately after the `mchunk_t` structure in memory,
 * within the corresponding `mbin_t` region.
 */
typedef struct s_mchunk
{
    /** @brief The state of the `mchunk_t` (allocated or free). */
    enum e_mchunk_state state;

    /**
     * @brief The total size of this `mchunk_t`, including its metadata.
     *
     * The referenced data can be retrieved using:
     * 
     * The next `t_mchunk` pointer can be retrieved using:
    */
    size_t              size;
    /**
     * @brief The total size of the previous `mchunk_t`, including its metadata.
     *
     * The previous `t_mchunk` pointer can be retrieved using:
    */
    size_t              prev_size;

    /** @brief Pointer to the next free chunk in the `mbin_t`. NULL if last in doubly-linked-list. */
    struct s_mchunk     *next_free_chunk;
    /** @brief Pointer to the next free chunk in the `mbin_t`. NULL if first in doubly-linked-list. */
    struct s_mchunk     *prev_free_chunk;
} mchunk_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif