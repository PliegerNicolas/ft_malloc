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

static inline bool  should_partition_mchunk_for_usage(mchunk_t *free_mchunk, size_t used_allocation_size)
{
    if (!free_mchunk || free_mchunk->allocation_size < used_allocation_size)
        return true;

    return ALIGN_UP(free_mchunk->allocation_size, ALIGNMENT_BOUNDARY) - used_allocation_size > MCHUNK_HEADER_SIZE; // /!\ not tested.
}

static mchunk_t *use_mchunk_in_place(mregion_t **mregion, mchunk_t **free_mchunk, size_t new_allocation_size)
{
    mchunk_t    *used_mchunk;
    mchunk_t    *next_free_mchunk;

    if (!mregion || !*mregion || !free_mchunk || !*free_mchunk)
        return printerr("use_mchunk_in_place()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (should_partition_mchunk_for_usage(*free_mchunk, new_allocation_size) || !does_mregion_contain_mchunk(*mregion, *free_mchunk))
        return printerr("use_mchunk_in_place()", "Wrong parameters", NULL), STATUS_FAILURE;

    used_mchunk = *free_mchunk;
    next_free_mchunk = used_mchunk->next_free_mchunk;

    if (used_mchunk->prev_free_mchunk)
        used_mchunk->prev_free_mchunk->next_free_mchunk = used_mchunk->next_free_mchunk;
    if (used_mchunk->next_free_mchunk)
        used_mchunk->next_free_mchunk->prev_free_mchunk = used_mchunk->prev_free_mchunk;
    used_mchunk->next_free_mchunk = NULL;
    used_mchunk->prev_free_mchunk = NULL;

    used_mchunk->allocation_size = new_allocation_size;
    used_mchunk->state = USED;

    if ((*mregion)->mbin == used_mchunk)
        (*mregion)->mbin = next_free_mchunk;

    return (*free_mchunk = next_free_mchunk), used_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *use_mchunk(mregion_t **mregion, mchunk_t *original_mchunk, size_t allocation_size)
{
    // mchunk_t    *used_mchunk;
    mchunk_t    *used_mchunk;
    mchunk_t    *remainder_mchunk;

    if (!mregion || !*mregion || !original_mchunk)
        return printerr("use_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;
    if (!does_mregion_contain_mchunk(*mregion, original_mchunk) || original_mchunk->state != FREE)
        return STATUS_FAILURE;

    try_coalesce_with_neighboring_free_mchunks(*mregion, &original_mchunk);

    if (should_partition_mchunk_for_usage(original_mchunk, allocation_size))
    {
        original_mchunk->state = USED;
        remainder_mchunk = original_mchunk;
        used_mchunk = partition_mchunk(mregion, &remainder_mchunk, allocation_size);
    }
    else
        used_mchunk = use_mchunk_in_place(mregion, &original_mchunk, allocation_size);

    if (used_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;

    return ((*mregion)->used_mchunks += 1), used_mchunk;
}
