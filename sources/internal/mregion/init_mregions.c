/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 17:30:32 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-01 17:30:32 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/**
 * @warning `mregion->size` should be set.
*/
static void init_mregion_mbin(mregion_t *mregion, size_t mregion_size)
{
    mchunk_t    *mbin;

    if (!mregion)
        return;

    mbin = GET_MREGION_FIRST_MCHUNK(mregion);
    *mbin = (mchunk_t) {
        .state = FREE,
        .allocation_size = mregion_size - (MREGION_HEADER_SIZE + MCHUNK_HEADER_SIZE),
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    mregion->mbin = mbin;
    (void)get_max_allocation_size(mbin->allocation_size);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    init_mregion(mregion_t **mregion, size_t allocation_size)
{
    size_t  mregion_size;

    if (!mregion || *mregion != NULL)
        return STATUS_FAILURE;

    if (allocation_size == 0)
        return (*mregion = NULL), STATUS_SUCCESS;

    mregion_size = map_allocation_size_to_mregion_size(allocation_size);

    if ((*mregion = mmap_mregion(mregion_size)) == STATUS_FAILURE)
        return (*mregion = NULL), STATUS_FAILURE;

    **mregion = (mregion_t) {
        .size = mregion_size,
        .mbin = NULL,
        .used_mchunks = 0,
        .next = NULL,
        .prev = NULL,
    };

    init_mregion_mbin(*mregion, mregion_size);
    
    return STATUS_SUCCESS;
}

status_t    init_mregions(mregion_t **mregion, size_t allocation_size, size_t mregions_count)
{
    mregion_t   *new_mregion;

    if (!mregion)
        return STATUS_FAILURE;

    for (size_t i = 0; i< mregions_count; i++)
    {
        new_mregion = NULL;
        if (init_mregion(&new_mregion, allocation_size) == STATUS_FAILURE)
            return STATUS_FAILURE;
        prepend_mregion(mregion, new_mregion);
    }

    return STATUS_SUCCESS;
}
