/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coalesce_free_mchunks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 21:08:41 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-09 21:08:41 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    coalesce_with_next_free_mchunks(mchunk_t *mchunk, mchunk_t *next_mchunk)
{
    size_t  merged_allocation_size;

    if (!mchunk || !next_mchunk)
        return;
    
    if (mchunk->state != FREE || next_mchunk->state != FREE)
        return;

    if (GET_NEXT_MCHUNK(mchunk) != next_mchunk)
        return;

    merged_allocation_size = ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) + GET_MCHUNK_SIZE(next_mchunk->allocation_size);

    // Relink mchunks.
    if (next_mchunk->next_free_mchunk)
    {
        next_mchunk->next_free_mchunk->prev_free_mchunk = mchunk;
        next_mchunk->next_free_mchunk->prev_allocation_size = merged_allocation_size;
    }
    mchunk->next_free_mchunk = next_mchunk->next_free_mchunk;
    mchunk->allocation_size = merged_allocation_size;
}

void    coalesce_with_prev_free_mchunks(mchunk_t **mchunk, mchunk_t *prev_mchunk)
{
    mregion_t   **mregion;
    size_t      merged_allocation_size;

    if ((!mchunk || !*mchunk) || !prev_mchunk)
        return;
    
    if ((*mchunk)->state != FREE || prev_mchunk->state != FREE)
        return;

    if (GET_NEXT_MCHUNK(prev_mchunk) != *mchunk)
        return;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, *mchunk)) == STATUS_FAILURE)
        return;

    merged_allocation_size = ALIGN_UP(prev_mchunk->allocation_size, ALIGNMENT_BOUNDARY) + GET_MCHUNK_SIZE((*mchunk)->allocation_size);

    // Relink mchunks.)
    if ((*mchunk)->next_free_mchunk)
    {
        (*mchunk)->next_free_mchunk->prev_free_mchunk = prev_mchunk;
        (*mchunk)->next_free_mchunk->prev_allocation_size = merged_allocation_size;
    }
    prev_mchunk->next_free_mchunk = (*mchunk)->next_free_mchunk;
    prev_mchunk->allocation_size = merged_allocation_size;

    // Update mregion->mbin if necessary.
    if ((unsigned char *)(*mregion)->mbin > (unsigned char *)prev_mchunk)
        (*mregion)->mbin = prev_mchunk;

    // Relocate given free_mchunk. It has been merged either way. :)
    *mchunk = prev_mchunk;
}
