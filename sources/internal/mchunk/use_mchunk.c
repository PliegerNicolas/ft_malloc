/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 22:12:26 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 22:12:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static mchunk_t *use_exact_match_mchunk(mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *prev_free_mchunk;
    mchunk_t    *next_free_mchunk;
    
    // Removing the `mchunk_t` from the free `mchunk_t` mbin, infers it is used.

    if (!free_mchunk || free_mchunk->allocation_size != allocation_size)
        return STATUS_FAILURE;

    prev_free_mchunk = free_mchunk->prev_free_mchunk;
    next_free_mchunk = free_mchunk->next_free_mchunk;
        
    prev_free_mchunk->next_free_mchunk = next_free_mchunk;
    next_free_mchunk->prev_free_mchunk = prev_free_mchunk;

    free_mchunk->prev_free_mchunk = NULL;
    free_mchunk->next_free_mchunk = NULL;

    return free_mchunk;
}

static mchunk_t *partition_and_use_mchunk(mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *right_mchunk;
    mchunk_t    *left_mchunk;
    mchunk_t    original_mchunk_data;
    size_t      right_mchunk_size;
    size_t      left_mchunk_size;

    right_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);
    left_mchunk_size = GET_MCHUNK_PADDED_SIZE(free_mchunk) - right_mchunk_size;

    if (!free_mchunk || free_mchunk->allocation_size < right_mchunk_size)
        return STATUS_FAILURE;

    original_mchunk_data = *free_mchunk;

    left_mchunk = free_mchunk;
    right_mchunk = (mchunk_t *)((unsigned char *)free_mchunk + (left_mchunk_size - right_mchunk_size));

    *left_mchunk = (mchunk_t) {
        .allocation_size = left_mchunk_size - MCHUNK_HEADER_PADDED_SIZE,
        .prev_allocation_size = original_mchunk_data.prev_allocation_size,
        .next_free_mchunk = original_mchunk_data.next_free_mchunk,
        .prev_free_mchunk = original_mchunk_data.prev_free_mchunk,
    };

    *right_mchunk = (mchunk_t) {
        .allocation_size = right_mchunk_size - MCHUNK_HEADER_PADDED_SIZE,
        .prev_allocation_size = original_mchunk_data.allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    return right_mchunk;
}

/**
 * @brief ...
*/
mchunk_t    *use_mchunk(mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *next_mchunk;
    mchunk_t    *used_mchunk;

    if (!free_mchunk || free_mchunk->allocation_size < allocation_size)
        return STATUS_FAILURE;

    if (free_mchunk->allocation_size == allocation_size)
        used_mchunk = use_exact_match_mchunk(free_mchunk, allocation_size);
    else
        used_mchunk = partition_and_use_mchunk(free_mchunk, allocation_size);

    if (used_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;

    return used_mchunk;
}