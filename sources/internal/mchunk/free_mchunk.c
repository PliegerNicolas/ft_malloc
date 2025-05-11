/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 03:44:54 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 03:44:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *free_mchunk(mregion_t *mregion, mchunk_t *used_mchunk)
{
    mchunk_t    *free_mchunk;

    if (!mregion || !used_mchunk)
        return STATUS_FAILURE;
    if (!does_mregion_contain_mchunk(mregion, used_mchunk) || used_mchunk->state != USED)
        return STATUS_FAILURE;

    free_mchunk = used_mchunk;
    free_mchunk->state = FREE;
    free_mchunk->allocation_size = ALIGN_UP(free_mchunk->allocation_size, ALIGNMENT_BOUNDARY);

    if ((insert_free_mchunk_in_mregion_mbin(mregion, free_mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    // coalesce ?

    return (mregion->used_mchunks -= 1), free_mchunk;
}
