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

static inline bool  is_mchunk_too_small_to_shrink(mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return true;
    return ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) < GET_MCHUNK_SIZE(reallocation_size);
}

static void    update_mbin_if_necessary(mregion_t *mregion, mchunk_t *free_mchunk)
{
    if (!mregion || !free_mchunk)
        return;

    if (!mregion->mbin || mregion->mbin->state != FREE)
        mregion->mbin = free_mchunk;

    while (mregion->mbin->prev_free_mchunk)
        mregion->mbin = mregion->mbin->prev_free_mchunk;
}

static mchunk_t *shrink_mchunk_by_partitioning(mregion_t *mregion, mchunk_t **original_mchunk, size_t reallocation_size)
{   
    mchunk_t    *leading_mchunk;
 
    if (!original_mchunk || !*original_mchunk)
        return STATUS_FAILURE;

    if (!does_mregion_contain_mchunk(mregion, *original_mchunk) || is_mchunk_too_small_to_shrink(*original_mchunk, reallocation_size))
        return STATUS_FAILURE;

    if ((leading_mchunk = partition_mchunk(original_mchunk, reallocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    update_mbin_if_necessary(mregion, *original_mchunk);
    return leading_mchunk;
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

    if ((mregion = get_mregion_by_mchunk(marena, mchunk, mchunk->allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if (is_mchunk_too_small_to_shrink(mchunk, reallocation_size))
        return migrate_mchunk_to_new_mregion(marena, mchunk, reallocation_size);
    
    if ((shrunk_mchunk = shrink_mchunk_by_partitioning(*mregion, &mchunk, reallocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    free_mchunk = mchunk; // due to prev function call.

    try_coalesce_with_next_free_mchunk(*mregion, &free_mchunk);

    return shrunk_mchunk;
}
