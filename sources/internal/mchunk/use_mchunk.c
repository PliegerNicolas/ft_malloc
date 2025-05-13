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

static inline bool  should_partition_mchunk_for_usage(mchunk_t *mchunk, size_t new_allocation_size)
{
    if (!mchunk)
        return true;

    return mchunk->allocation_size - new_allocation_size > MCHUNK_HEADER_SIZE;
}

static mchunk_t *use_in_place(mchunk_t **free_mchunk, size_t new_allocation_size)
{
    mchunk_t    *used_mchunk;
    mchunk_t    *prev_free_mchunk, *next_free_mchunk;

    if (!free_mchunk || !*free_mchunk || should_partition_mchunk_for_usage(*free_mchunk, new_allocation_size))
        return STATUS_FAILURE;

    prev_free_mchunk = (*free_mchunk)->prev_free_mchunk;
    next_free_mchunk = (*free_mchunk)->next_free_mchunk;

    used_mchunk = *free_mchunk;
    *used_mchunk = (mchunk_t) {
        .state = USED,
        .allocation_size = new_allocation_size,
        .prev_allocation_size = (*free_mchunk)->prev_allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    if (prev_free_mchunk)
        prev_free_mchunk->next_free_mchunk = next_free_mchunk;
    if (next_free_mchunk)
        next_free_mchunk->prev_free_mchunk = prev_free_mchunk;

    return (*free_mchunk = next_free_mchunk), used_mchunk;
}

static mchunk_t *use_and_partition_mchunk(mregion_t **mregion, mchunk_t **original_mchunk, size_t allocation_size)
{
    mchunk_t    *leading_mchunk;

    if (!original_mchunk || !*original_mchunk)
        return STATUS_FAILURE;

    (*original_mchunk)->state = USED;
    if ((leading_mchunk = partition_mchunk(mregion, original_mchunk, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    
    return leading_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *use_mchunk(mregion_t **mregion, mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;

    if (!mregion || !*mregion || !free_mchunk)
        return printerr("use_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;
    if (!does_mregion_contain_mchunk(*mregion, free_mchunk) || free_mchunk->state != FREE)
        return STATUS_FAILURE;

    try_coalesce_with_neighboring_free_mchunks(*mregion, &free_mchunk);

    // (free_mchunk->allocation_size - allocation_size) > MCHUNK_HEADER_SIZE;

    if (!should_partition_mchunk_for_usage(free_mchunk, allocation_size))
        used_mchunk = use_in_place(&free_mchunk, allocation_size);
    else
        used_mchunk = use_and_partition_mchunk(mregion, &free_mchunk, allocation_size);

    if (used_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;

    return ((*mregion)->used_mchunks += 1), used_mchunk;
}
