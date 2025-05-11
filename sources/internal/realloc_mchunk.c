/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_mchunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:14:59 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:14:59 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static bool should_migrate_to_new_mregion_type(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size)
{
    mregion_t   **recognized_mregion_head;
    mregion_t   **desired_mregion_head;

    if (!mchunk)
        return true;

    recognized_mregion_head = map_allocation_size_to_marena_mregion_head(marena, mchunk->allocation_size);
    if (!recognized_mregion_head || !*recognized_mregion_head)
        return true;

    desired_mregion_head = map_allocation_size_to_marena_mregion_head(marena, reallocation_size);
    if (!desired_mregion_head || !*desired_mregion_head)
        return true;
    
    return *recognized_mregion_head != *desired_mregion_head;
}

static inline bool  mchunk_needs_resize(mchunk_t *mchunk, size_t reallocation_size)
{
    return mchunk->allocation_size != reallocation_size;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *realloc_mchunk(marena_t *marena, mchunk_t *used_mchunk, size_t reallocation_size)
{
    mregion_t   **mregion;
    mchunk_t    *potentially_relocated_mchunk;

    if (!used_mchunk || used_mchunk->state != USED)
        return STATUS_FAILURE;

    if (reallocation_size == 0)
        return free_mchunk_or_mregion(marena, used_mchunk), NULL;
    
    if (should_migrate_to_new_mregion_type(marena, used_mchunk, reallocation_size))
        return move_mchunk_to_new_mregion(marena, used_mchunk, reallocation_size);

    if (reallocation_size > used_mchunk->allocation_size)
        potentially_relocated_mchunk = NULL; // grow
    else
        potentially_relocated_mchunk = NULL; // shrink

    return potentially_relocated_mchunk;
}
