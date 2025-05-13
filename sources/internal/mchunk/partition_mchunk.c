/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_mchunk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 22:14:37 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 22:14:37 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  can_mchunk_be_partitioned(mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return false;

    return ALIGN_UP(mchunk->allocation_size, ALIGNMENT_BOUNDARY) >= GET_MCHUNK_SIZE(reallocation_size);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

/**
 * @brief Partitions the existing `mchunk_t` into two contiguous ones.
 * 
 * @returns The leading `mchunk_t`. original_mchunk is set to the remainder FREE `mchunk_t`.
 * @warning Set the desired state of the leading `mchunk_t` before partitioning to ensure `mregion->mbin` is correctly updated.
*/
mchunk_t    *partition_mchunk(mregion_t **mregion, mchunk_t **original_mchunk, size_t new_allocation_size)
{
    mchunk_t    *leading_mchunk, *remainder_mchunk;
    mchunk_t    og_mchunk_cache;

    if (!mregion || !*mregion || !original_mchunk || !*original_mchunk)
        return printerr("partition_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (!does_mregion_contain_mchunk(*mregion, *original_mchunk) || !can_mchunk_be_partitioned(*original_mchunk, new_allocation_size))
        return printerr("partition_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    leading_mchunk = *original_mchunk;
    remainder_mchunk = (mchunk_t *)((unsigned char *)leading_mchunk + GET_MCHUNK_SIZE(new_allocation_size));
    og_mchunk_cache = **original_mchunk;

    leading_mchunk->state = og_mchunk_cache.state; // removable
    leading_mchunk->allocation_size = new_allocation_size;
    leading_mchunk->prev_allocation_size = og_mchunk_cache.prev_allocation_size; // removable

    remainder_mchunk->state = FREE;
    remainder_mchunk->allocation_size = ALIGN_UP(og_mchunk_cache.allocation_size, ALIGNMENT_BOUNDARY) - GET_MCHUNK_SIZE(leading_mchunk->allocation_size);
    remainder_mchunk->prev_allocation_size = leading_mchunk->allocation_size;

    if (og_mchunk_cache.state == FREE)
    {
        leading_mchunk->next_free_mchunk = remainder_mchunk;
        leading_mchunk->prev_free_mchunk = og_mchunk_cache.prev_free_mchunk;
        if (leading_mchunk->prev_free_mchunk)
            leading_mchunk->prev_free_mchunk->next_free_mchunk = leading_mchunk;

        remainder_mchunk->next_free_mchunk = og_mchunk_cache.next_free_mchunk;
        remainder_mchunk->prev_free_mchunk = leading_mchunk;
        if (remainder_mchunk->next_free_mchunk)
        {
            remainder_mchunk->next_free_mchunk->prev_free_mchunk = remainder_mchunk;
            if (GET_NEXT_MCHUNK(remainder_mchunk) == remainder_mchunk->next_free_mchunk)
                remainder_mchunk->next_free_mchunk->prev_allocation_size = remainder_mchunk->allocation_size;
        }

        if (!(*mregion)->mbin || (unsigned char*)((*mregion)->mbin) > (unsigned char*)leading_mchunk)
            (*mregion)->mbin = leading_mchunk;
    }
    else
    {
        leading_mchunk->next_free_mchunk = NULL;
        leading_mchunk->prev_free_mchunk = NULL;

        remainder_mchunk->next_free_mchunk = og_mchunk_cache.next_free_mchunk;
        remainder_mchunk->prev_free_mchunk = og_mchunk_cache.prev_free_mchunk;
        if (remainder_mchunk->prev_free_mchunk)
            remainder_mchunk->prev_free_mchunk->next_free_mchunk = leading_mchunk;
        if (remainder_mchunk->next_free_mchunk)
        {
            remainder_mchunk->next_free_mchunk->prev_free_mchunk = remainder_mchunk;
            if (GET_NEXT_MCHUNK(remainder_mchunk) == remainder_mchunk->next_free_mchunk)
                remainder_mchunk->next_free_mchunk->prev_allocation_size = remainder_mchunk->allocation_size;
        }

        if (!(*mregion)->mbin || (*mregion)->mbin == leading_mchunk || (unsigned char*)((*mregion)->mbin) > (unsigned char*)remainder_mchunk)
            (*mregion)->mbin = remainder_mchunk;
    }

    return (*original_mchunk = remainder_mchunk), leading_mchunk;
}
