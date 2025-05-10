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

void    coalesce_free_mchunks(mchunk_t *mchunk, mchunk_t *next_mchunk)
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
