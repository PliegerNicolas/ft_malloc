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
 * @struct s_arena
 * @brief Doubly-linked-list of arenas. Contains a fixed number of `mbin_t` and some metadata.
 * 
 * Each `mbin_t` is dedicated to managing memory chunks (`mchunk_t`) of specific size ranges.
 * The `mchunk_t` specify where the user's data is stored in the `mbin_t`s.
*/
typedef struct s_arena
{
    /** @brief A fixed-size array of pointers to `mbin_t` structures, one for each supported bin type. */
    mbin_t          bins[NUM_MBIN_TYPES];

    struct s_arena  *next;
    struct s_arena  *prev;
} arena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif