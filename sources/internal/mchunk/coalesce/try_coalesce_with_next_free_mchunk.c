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

void    try_coalesce_with_next_free_mchunk(mregion_t *mregion, mchunk_t *mchunk)
{
    mchunk_t    *next_mchunk;

    if (!mregion || !mchunk)
        return;

    if (!does_mregion_contain_mchunk(mregion, mchunk))
        return;

    next_mchunk = GET_NEXT_MCHUNK(mchunk);
    if (!next_mchunk || !does_mregion_contain_mchunk(mregion, next_mchunk) || is_on_mregion_boundary(mregion, next_mchunk))
        return;

    if (next_mchunk->state != FREE)
        return;

    mchunk->allocation_size += GET_MCHUNK_SIZE(next_mchunk->allocation_size);

    if (next_mchunk->next_free_mchunk)
    {
        next_mchunk->next_free_mchunk->prev_free_mchunk = next_mchunk->prev_free_mchunk;
        next_mchunk->next_free_mchunk->prev_allocation_size = mchunk->allocation_size;
    }

    if (next_mchunk->prev_free_mchunk)
        next_mchunk->prev_free_mchunk->next_free_mchunk = next_mchunk->next_free_mchunk;

    if (mregion->mbin == next_mchunk)
        mregion->mbin = next_mchunk->next_free_mchunk;
}
