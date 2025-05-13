/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mchunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:14:49 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:14:49 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  is_mregion_full(mregion_t *mregion)
{
    if (!mregion)
        return true;

    return mregion->mbin == NULL;
}

// Because we want unbound mregions to have a high in-place growth space availability.
static inline bool  is_mregion_full_enough(mregion_t *mregion, size_t allocation_size)
{
    if (!mregion)
        return true;

    if (IS_BOUND_MREGION(allocation_size))
        return false;

    return mregion->used_mchunks >= MCHUNKS_PER_UNBOUND_MREGION;
}

static mchunk_t *find_or_generate_best_fit_free_mchunk(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion_head;
    mregion_t   **current_mregion;
    mchunk_t    *best_fit_free_mchunk;

    if ((mregion_head = map_allocation_size_to_marena_mregion_head(marena, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    if (!*mregion_head && (init_mregion(mregion_head, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    current_mregion = mregion_head;
    while (*current_mregion)
    {
        if (!is_mregion_full(*current_mregion) && !is_mregion_full_enough(*current_mregion, allocation_size))
        {
            best_fit_free_mchunk = select_best_fit_mbin_mchunk((*current_mregion)->mbin, allocation_size);
            if (best_fit_free_mchunk)
                return best_fit_free_mchunk;
        }

        current_mregion = &(*current_mregion)->next;
    }

    if (!*current_mregion && init_mregion(current_mregion, allocation_size) == STATUS_FAILURE)
        return STATUS_FAILURE;

    best_fit_free_mchunk = (*current_mregion)->mbin;
    return best_fit_free_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *alloc_mchunk(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion;
    mchunk_t    *free_mchunk, *used_mchunk;

    if (!marena)
        return printerr("alloc_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    if ((free_mchunk = find_or_generate_best_fit_free_mchunk(marena, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if ((mregion = get_mregion_by_mchunk(marena, free_mchunk, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    
    if ((used_mchunk = use_mchunk(mregion, free_mchunk, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return used_mchunk;
}
