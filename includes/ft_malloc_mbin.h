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

/*
* One `mbin_t` size should be "open". In other words, it should be able to accomodate
* all the chunks that are too big for the other `mbin_t`s.
* In our case that's our `MBIN_LARGE`. For each large `mchunk_t`, a new `mbin_t`
* is create and thus a new `mmap()` call is made.
*/

/* CONSTANTS */

/** @brief Configurable arbitrary value for how many allocations should ideally be available per `mbin_t`. */
# define TARGET_MIN_ALLOCATIONS_PER_MBIN ((size_t)(100))
/** @brief Configurable arbitrary value for how many allocations should ideally be available per large `mbin_t`. */
# define TARGET_MIN_ALLOCATIONS_PER_LARGE_MBIN ((size_t)1)

/** @brief Configurable arbitrary value for how many tiny bins should be created on initialization. */
# define TARGET_INITIAL_TINY_MBINS ((size_t)3)
/** @brief Configurable arbitrary value for how many small bins should be created on initialization. */
# define TARGET_INITAL_SMALL_MBINS ((size_t)3)

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Size of a tiny `mbin_t`. */
# define TINY_MBIN_SIZE ((size_t)(ALIGN_UP(TARGET_MIN_ALLOCATIONS_PER_MBIN * TINY_MCHUNK_SIZE, PAGE_SIZE)))
/** @brief Size of a small `mbin_t`. */
# define SMALL_MBIN_SIZE ((size_t)(ALIGN_UP(TARGET_MIN_ALLOCATIONS_PER_MBIN * SMALL_MCHUNK_SIZE, PAGE_SIZE)))

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @enum e_mbin_type
 * @brief Enumeration representing the supported `mbin_t` categories.
 *
 * These categories are used to identify the type of each `mbin_t` in an array of size `NUM_MBIN_TYPES`.
*/
enum e_mbin_type
{
    /** @brief Category for `mbin_t` structures managing tiny `mchunk_t` allocations. */
    MBIN_TINY,
    
    /** @brief Category for `mbin_t` structures managing small `mchunk_t` allocations. */
    MBIN_SMALL,
    
    /** @brief Category for `mbin_t` structures managing large `mchunk_t` allocations. */
    MBIN_LARGE,

    /** @brief Number of supported `mbin_t` categories. */
    NUM_MBIN_TYPES
};

/**
 * @struct s_mbin
 * @brief A doubly-linked-list of memory bins.
 * It contais mmap()-allocated memory regions ready to be partitioned into `mchunk_t`s.
*/
typedef struct s_mbin
{
    /** @brief The `mbin_t`s size: the amount of memory allocated by `mmap()`. */
    size_t          size;

    /** @brief The `mbin_t`s initial chunk: the original pointer returned by `mmap()`. */
    mchunk_t        *initial_chunk;

    /** @brief Pointer to the next `mbin_t` in the doubly-linked list. NULL if this is the last. */
    struct s_mbin   *next;
    
    /** @brief Pointer to the previous `mbin_t` in the doubly-linked list. NULL if this is the first. */
    struct s_mbin   *prev;
} mbin_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif