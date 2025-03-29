/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 22:11:56 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 22:11:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

heap_t  gheap;

static mbin_t   initialize_bin(enum e_mbin_type type)
{
    mbin_t  new_bin;

    new_bin.initial_chunk = NULL;
    new_bin.size = 0;

    new_bin.next = NULL;
    new_bin.prev = NULL;

    return new_bin;
}

static void initialize_arena(arena_t *arena)
{
    for (enum e_mbin_type bin_type; bin_type < NUM_MBIN_TYPES; ++bin_type)
        arena->bins[bin_type] = initialize_bin(bin_type);

    arena->next = NULL;
    arena->prev = NULL;
}

heap_t  initialize_heap()
{
    heap_t  new_heap;
    mbin_t  **bins;

    new_heap.is_initialized = true;
    initialize_arena(&new_heap.arenas);

    return new_heap;
}
