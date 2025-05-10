/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_mchunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 17:27:30 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 17:27:30 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  mchunk_needs_resize(mchunk_t *mchunk, size_t new_allocation_size)
{
    return mchunk->allocation_size != new_allocation_size;
}

static bool should_switch_mregion_type(mchunk_t *mchunk, size_t new_allocation_size)
{
    mregion_t   **recognized_mregion_head;
    mregion_t   **desired_mregion_head;

    if (!mchunk)
        return true;

    recognized_mregion_head = map_allocation_size_to_marena_mregion_head(&gmarena, mchunk->allocation_size);
    if (!recognized_mregion_head || !*recognized_mregion_head)
        return true;

    desired_mregion_head = map_allocation_size_to_marena_mregion_head(&gmarena, new_allocation_size);
    if (!desired_mregion_head || !*desired_mregion_head)
        return true;

    return *recognized_mregion_head != *desired_mregion_head;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *realloc_mchunk(mchunk_t *original_mchunk, size_t new_allocation_size)
{
    if (!original_mchunk)
        return STATUS_FAILURE;

    if (new_allocation_size == 0)
        return free_mchunk(original_mchunk), NULL;
    else if (!mchunk_needs_resize(original_mchunk, new_allocation_size))
        return original_mchunk;

    if (should_switch_mregion_type(original_mchunk, new_allocation_size))
        return move_mchunk_to_new_mregion(original_mchunk, new_allocation_size);

    if (new_allocation_size > original_mchunk->allocation_size)
        return grow_mchunk(original_mchunk, new_allocation_size);
    else
        return shrink_mchunk(original_mchunk, new_allocation_size);
}
