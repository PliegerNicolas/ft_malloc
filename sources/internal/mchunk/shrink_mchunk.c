/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shrink_mchunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 21:37:55 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-09 21:37:55 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  has_enough_space_to_shrink_in_place(mchunk_t *mchunk, size_t new_allocation_size)
{
    return mchunk->allocation_size >= GET_MCHUNK_SIZE(new_allocation_size);
}

mchunk_t    *shrink_mchunk_by_partitioning(mchunk_t *mchunk, size_t new_allocation_size)
{
    mregion_t   **mregion;
    size_t      remaining_allocation_size;
    mchunk_t    *remaining_free_mchunk;

    if (!mchunk || mchunk->allocation_size < GET_MCHUNK_SIZE(new_allocation_size))
        return STATUS_FAILURE;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    remaining_allocation_size = mchunk->allocation_size - GET_MCHUNK_SIZE(new_allocation_size);
    mchunk->allocation_size = new_allocation_size;

    remaining_free_mchunk = GET_NEXT_MCHUNK(mchunk);
    *remaining_free_mchunk = (mchunk_t) {
        .state = FREE,
        .allocation_size = remaining_allocation_size,
        .prev_allocation_size = mchunk->allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    insert_free_mchunk_in_mregion_mbin(*mregion, remaining_free_mchunk);
    coalesce_with_next_free_mchunks(remaining_free_mchunk, remaining_free_mchunk->next_free_mchunk);

    return mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *shrink_mchunk(mchunk_t *original_mchunk, size_t new_allocation_size)
{
    if (!original_mchunk || new_allocation_size >= original_mchunk->allocation_size)
        return STATUS_FAILURE;

    if (!has_enough_space_to_shrink_in_place(original_mchunk, new_allocation_size))
        return move_mchunk_to_new_mregion(original_mchunk, new_allocation_size);

    return shrink_mchunk_by_partitioning(original_mchunk, new_allocation_size);
}
