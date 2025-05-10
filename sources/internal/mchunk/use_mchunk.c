/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 03:44:35 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 03:44:35 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static mchunk_t *use_on_exact_match(mchunk_t **free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;
    mchunk_t    *prev_free_mchunk, *next_free_mchunk;

    if (!free_mchunk || !*free_mchunk)
        return STATUS_FAILURE;

    prev_free_mchunk = (*free_mchunk)->prev_free_mchunk;
    next_free_mchunk = (*free_mchunk)->next_free_mchunk;

    used_mchunk = *free_mchunk;
    used_mchunk->state = USED;
    used_mchunk->next_free_mchunk = NULL;
    used_mchunk->prev_free_mchunk = NULL;

    if (prev_free_mchunk)
        prev_free_mchunk->next_free_mchunk = next_free_mchunk;
    if (next_free_mchunk)
        next_free_mchunk->prev_free_mchunk = prev_free_mchunk;

    return (*free_mchunk = next_free_mchunk), used_mchunk;
}

static mchunk_t *use_and_partition_mchunk(mchunk_t **original_mchunk, size_t allocation_size)
{
    mchunk_t    *leading_mchunk;

    if ((leading_mchunk = partition_mchunk(original_mchunk, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    
    leading_mchunk->state = USED;
    return leading_mchunk;
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

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *use_mchunk(mregion_t *mregion, mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;

    if (!mregion || !free_mchunk)
        return printerr("use_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;
    if (!does_mregion_contain_mchunk(mregion, free_mchunk) || free_mchunk->state != FREE)
        return STATUS_FAILURE;

    try_coalesce_with_neighboring_free_mchunks(mregion, &free_mchunk);

    if (free_mchunk->allocation_size == allocation_size)
        used_mchunk = use_on_exact_match(&free_mchunk, allocation_size);
    else
        used_mchunk = use_and_partition_mchunk(&free_mchunk, allocation_size);

    if (used_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;

    update_mbin_if_necessary(mregion, free_mchunk);
    return (mregion->used_mchunks += 1), used_mchunk;
}
