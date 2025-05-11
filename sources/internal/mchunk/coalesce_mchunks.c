/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coalesce_mchunks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 13:43:38 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 13:43:38 by nplieger         ###   ########.fr       */
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

mchunk_t    *try_coalesce_with_next_mchunk(mregion_t *mregion, mchunk_t *mchunk)
{
    mchunk_t    *neighbor;

    if (!mregion)
        return STATUS_FAILURE;

    if (!mchunk)
        return mchunk;
    if (!does_mregion_contain_mchunk(mregion, mchunk))
        return STATUS_FAILURE;

    neighbor = GET_NEXT_MCHUNK(mchunk);
    if (is_on_mregion_boundary(mregion, neighbor))
        return mchunk;
    else if (!neighbor || !does_mregion_contain_mchunk(mregion, neighbor))
        return STATUS_FAILURE;

    if (neighbor->state != FREE)
        return mchunk;

    if (mchunk->state == USED && neighbor->next_free_mchunk)
        merge_used_with_free_mchunk(mchunk, neighbor);
    else
        merge_free_with_free_mchunk(mchunk, neighbor);

    return mchunk;
}

mchunk_t    *try_coalesce_with_neighbors(mregion_t *mregion, mchunk_t *mchunk)
{
    mchunk_t    *prev_mchunk;
    if (!mregion)
        return STATUS_FAILURE;

    if (!mchunk)
        return mchunk;

    if ((mchunk = try_coalesce_with_next_mchunk(mregion, mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    prev_mchunk = mchunk->prev_free_mchunk;
    if ((prev_mchunk = try_coalesce_with_next_mchunk(mregion, mchunk->prev_free_mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return prev_mchunk ? prev_mchunk : mchunk;
}
