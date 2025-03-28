/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_arena.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:59:31 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:59:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_ARENA_H
# define FT_MALLOC_ARENA_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_mbin.h"

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @struct s_arena_config
 * @brief Contains configuration information about the `mbin_t` of a specific `arena_t`.
*/
typedef struct s_arena_config
{
    /** @brief Size of each `mbin_t` allocated through `mmap()`, per type. */
    size_t  mbin_sizes[NUM_MBIN_TYPES];
    
    /** @brief Size of each `mchunk_t` inside the corresponding `mbin_t`, per type. */
    size_t  mchunk_sizes[NUM_MBIN_TYPES];
} arena_config_t;

/**
 * @struct s_arena
 * @brief Contains a fixed number of `mbin_t` and some metadata.
 * 
 * Each `mbin_t` is dedicated to managing memory chunks (`mchunk_t`) of specific size ranges.
 * The `mchunk_t` specify where the user's data is stored in the `mbin_t`s.
*/
typedef struct s_arena
{
    /** @brief A fixed-size array of pointers to `mbin_t` structures, one for each bin type. */
    mbin_t          *bins[NUM_MBIN_TYPES];
    
    /** @brief Configuration for the `mbin_t`s in this arena, including bin and chunk sizes. */
    arena_config_t  config;
} arena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif