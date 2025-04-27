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
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    init_mregion(mregion_t **mregion, size_t allocation_size)
{
    size_t  mregion_size;

    if (!mregion || *mregion)
        return STATUS_FAILURE;

    if (allocation_size == 0 || allocation_size < MREGION_HEADER_SIZE)
        return (*mregion = NULL), STATUS_SUCCESS;

    mregion_size = map_allocation_size_to_mregion_size(allocation_size);

    *mregion = mmap_mregion(mregion_size);
    if (*mregion == STATUS_FAILURE)
        return (*mregion = NULL), STATUS_FAILURE;

    **mregion = (mregion_t) {
        .size = mregion_size,
        .mbin = NULL,
        .next = NULL,
    };

    init_mregion_mbin(*mregion, mregion_size);
    
    return STATUS_SUCCESS;
}
