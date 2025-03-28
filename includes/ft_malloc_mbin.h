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
/* *                                  MACROS                                 * */
/* *************************************************************************** */

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
 * @brief Represents a memory bin, stored in a doubly-linked list, 
 * containing an mmap()-allocated memory region ready to be partitioned into `mchunk_t`s.
*/
typedef struct s_mbin
{
    /** @brief The initial chunk of the `mbin_t`, also the original pointer returned by `mmap()`. */
    mchunk_t *initial_chunk;

    /** @brief Pointer to the next `mbin_t` in the doubly-linked list. NULL if this is the last. */
    struct s_mbin *next;
    
    /** @brief Pointer to the previous `mbin_t` in the doubly-linked list. NULL if this is the first. */
    struct s_mbin *prev;
} mbin_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif