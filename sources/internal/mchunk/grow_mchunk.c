/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 20:17:01 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 20:17:01 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  can_mchunk_grow_in_place(mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return false;
    return ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) >= reallocation_size;
}

static inline bool  can_mchunk_be_partitioned(mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return false;
    return ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) >= GET_MCHUNK_SIZE(reallocation_size);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *grow_mchunk(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size)
{
    mregion_t   **mregion;
    mchunk_t    *reallocated_mchunk;

    if (!marena || !mchunk || mchunk->allocation_size >= reallocation_size)
        return printerr("grow_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;
    else if (mchunk->allocation_size == reallocation_size)
        return mchunk;

    if (can_mchunk_grow_in_place(mchunk, reallocation_size))
        return (mchunk->allocation_size = reallocation_size), mchunk;

    if ((mregion = get_mregion_by_mchunk(marena, mchunk, mchunk->allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if (!try_coalesce_until_allocation_size_reached(*mregion, mchunk, reallocation_size))
        return migrate_mchunk_to_new_mregion(marena, mchunk, reallocation_size);

    if (!can_mchunk_be_partitioned(mchunk, reallocation_size))
        return migrate_mchunk_to_new_mregion(marena, mchunk, reallocation_size);
    reallocated_mchunk = partition_mchunk(mregion, &mchunk, reallocation_size);

    return reallocated_mchunk;
}
