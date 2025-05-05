/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 15:19:25 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-05 15:19:25 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void coalesce_free_mchunks(mchunk_t *mchunk, mchunk_t *next_mchunk)
{
    size_t  merged_allocation_size;

    if (!mchunk || !next_mchunk)
        return;

    if (mchunk->state != FREE || next_mchunk->state != FREE)
        return;

    if (GET_NEXT_MCHUNK(mchunk) != next_mchunk)
        return;
    
    /* Equivalence of:
    * ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) + (MCHUNK_HEADER_SIZE + next_mchunk->allocation_size) */
    merged_allocation_size = GET_MCHUNK_SIZE(mchunk->allocation_size) + next_mchunk->allocation_size;
    
    // Relink mchunks.
    if (next_mchunk->next_free_mchunk)
    {
        next_mchunk->next_free_mchunk->prev_free_mchunk = mchunk;
        next_mchunk->next_free_mchunk->prev_allocation_size = merged_allocation_size;
    }
    mchunk->next_free_mchunk = next_mchunk->next_free_mchunk;
    mchunk->allocation_size = merged_allocation_size;
        
}

static status_t insert_mchunk_in_mbin(mregion_t *mregion, mchunk_t *mchunk)
{
    mchunk_t    **insertion_pos;

    if (!mregion || !mchunk)
        return STATUS_FAILURE;

    if (mchunk->state != FREE)
        return STATUS_FAILURE;

    insertion_pos = &mregion->mbin;
    while (*insertion_pos && *insertion_pos < mchunk)
        insertion_pos = &(*insertion_pos)->next_free_mchunk;

    mchunk->prev_free_mchunk = (*insertion_pos)->prev_free_mchunk;
    if (*insertion_pos)
        (*insertion_pos)->prev_free_mchunk = mchunk;
    mchunk->next_free_mchunk = *insertion_pos;

    *insertion_pos = mchunk;

    return STATUS_SUCCESS;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    free_mchunk(mregion_t *mregion, mchunk_t *mchunk)
{
    if (!mregion || !mchunk)
        return STATUS_FAILURE;

    if (mchunk->state != USED)
        return STATUS_FAILURE;

    mchunk->state = FREE;

    if (insert_mchunk_in_mbin(mregion, mchunk) == STATUS_FAILURE)
        return STATUS_FAILURE;

    coalesce_free_mchunks(mchunk, mchunk->next_free_mchunk);
    coalesce_free_mchunks(mchunk->prev_free_mchunk, mchunk);

    return STATUS_SUCCESS;
}
