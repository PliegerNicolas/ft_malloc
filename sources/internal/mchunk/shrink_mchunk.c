/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink_mchunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 20:17:53 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 20:17:53 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  can_mchunk_shrink_in_place(mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return false;
    return reallocation_size >= ALIGN_DOWN(mchunk->allocation_size, ALIGNMENT_BOUNDARY);
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

mchunk_t    *shrink_mchunk(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size)
{
    mregion_t   **mregion;
    mchunk_t    *shrunk_mchunk;
    mchunk_t    *free_mchunk;

    if (!marena || !mchunk || mchunk->allocation_size <= reallocation_size)
        return printerr("shrink_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;
    else if (mchunk->allocation_size == reallocation_size)
        return mchunk;

    if (can_mchunk_shrink_in_place(mchunk, reallocation_size))
        return (mchunk->allocation_size = reallocation_size), mchunk;

    if ((mregion = get_mregion_by_mchunk(marena, mchunk, mchunk->allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if (!can_mchunk_be_partitioned(mchunk, reallocation_size))
        return migrate_mchunk_to_new_mregion(marena, mchunk, reallocation_size);

    if ((shrunk_mchunk = partition_mchunk(mregion, &mchunk, reallocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    free_mchunk = mchunk;

    try_coalesce_with_next_free_mchunk(*mregion, free_mchunk);

    return shrunk_mchunk;
}
