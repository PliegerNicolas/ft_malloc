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

static inline bool  has_enough_space(mchunk_t *mchunk, size_t new_allocation_size)
{
    return mchunk->allocation_size >= GET_MCHUNK_SIZE(new_allocation_size);
}

static mchunk_t *move_mchunk(mregion_t *mregion, mchunk_t *original_mchunk, size_t new_allocation_size)
{
    mchunk_t    *new_mchunk;

    if (!original_mchunk)
        return STATUS_FAILURE;

    if ((new_mchunk = malloc(new_allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    ft_memcpy(GET_MCHUNK_DATA_PTR(new_mchunk), GET_MCHUNK_DATA_PTR(original_mchunk), new_allocation_size);
    free_mchunk(mregion, original_mchunk);

    return new_mchunk;
}

static void split_mchunk(mregion_t *mregion, mchunk_t *mchunk, size_t new_allocation_size)
{
    size_t      left_mchunk_allocation_size;
    size_t      right_mchunk_allocation_size;
    mchunk_t    *new_free_mchunk;

    if (!mchunk)
        return;

    right_mchunk_allocation_size = new_allocation_size;
    left_mchunk_allocation_size = mchunk->allocation_size - GET_MCHUNK_SIZE(right_mchunk_allocation_size);
    
    mchunk->allocation_size = left_mchunk_allocation_size;

    new_free_mchunk = mchunk + GET_MCHUNK_SIZE(mchunk->allocation_size);
    *new_free_mchunk = (mchunk_t) {
        .state = FREE,
        .allocation_size = right_mchunk_allocation_size,
        .prev_allocation_size = left_mchunk_allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };
    
    insert_mchunk_in_mbin(mregion, new_free_mchunk);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *shrink_mchunk(mregion_t *mregion, mchunk_t *mchunk, size_t new_allocation_size)
{
    mchunk_t    *new_mchunk;

    if (!mchunk)
        return STATUS_FAILURE;

    if (!has_enough_space(mchunk, new_allocation_size))
    {
        if ((new_mchunk = move_mchunk(mregion, mchunk, new_allocation_size)) == STATUS_FAILURE)
            return STATUS_FAILURE;
        return new_mchunk;
    }

    split_mchunk(mregion, mchunk, new_allocation_size);
    return mchunk;
}
