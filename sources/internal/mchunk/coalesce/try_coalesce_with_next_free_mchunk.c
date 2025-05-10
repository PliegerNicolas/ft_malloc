/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_coalesce_with_next_free_mchunk.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 22:24:49 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 22:24:49 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void merge_used_with_free_mchunk(mchunk_t *mchunk, mchunk_t *neighbor)
{
    size_t      coalesced_allocation_size;

    if (!mchunk || !neighbor)
        return;

    if (!neighbor->next_free_mchunk)
        return;

    coalesced_allocation_size = mchunk->allocation_size + GET_MCHUNK_SIZE(neighbor->allocation_size);

    neighbor->next_free_mchunk->prev_free_mchunk = mchunk;
    neighbor->next_free_mchunk->prev_allocation_size = coalesced_allocation_size;
    mchunk->allocation_size = coalesced_allocation_size;
}

static void merge_free_with_free_mchunk(mchunk_t *mchunk, mchunk_t *neighbor)
{
    size_t      coalesced_allocation_size;

    if (!mchunk || !neighbor)
        return;

    coalesced_allocation_size = mchunk->allocation_size + GET_MCHUNK_SIZE(neighbor->allocation_size);

    if (neighbor->next_free_mchunk)
    {
        neighbor->next_free_mchunk->prev_free_mchunk = neighbor->prev_free_mchunk;
        neighbor->next_free_mchunk->prev_allocation_size = coalesced_allocation_size;
    }
    mchunk->next_free_mchunk = neighbor->next_free_mchunk;
    mchunk->allocation_size = coalesced_allocation_size;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    try_coalesce_with_next_free_mchunk(mregion_t *mregion, mchunk_t **mchunk)
{
    mchunk_t    *neighbor;

    if (!mregion || !mchunk || !*mchunk)
        return;

    if (!does_mregion_contain_mchunk(mregion, *mchunk))
        return;

    neighbor = GET_NEXT_MCHUNK(*mchunk);
    if (is_on_mregion_boundary(mregion, neighbor))
        return;
    else if (!neighbor || !does_mregion_contain_mchunk(mregion, neighbor))
        return;

    if (neighbor->state != FREE)
        return;

    if ((*mchunk)->state == USED && neighbor->next_free_mchunk)
        merge_used_with_free_mchunk(*mchunk, neighbor);
    else
        merge_free_with_free_mchunk(*mchunk, neighbor);
}
