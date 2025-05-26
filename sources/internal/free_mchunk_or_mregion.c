/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mchunk_or_mregion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 13:12:52 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 13:12:52 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief
 * 
 * We keep at least N bound mregions, where N is the amount of initialized bound mregions (`INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE`).
 * 
 * We keep no unbound mregions, as their storage size is unpredictable.
*/
mchunk_t    *free_mchunk_or_mregion(marena_t *marena, mchunk_t *used_mchunk)
{
    mregion_t   **mregion;
    mchunk_t    *freed_mchunk;
    size_t      free_bound_mregion_threshold;
    bool        is_bound_mregion;

    if (!used_mchunk || used_mchunk->state != USED)
        return printerr("free_mchunk_or_mregion()", "Wrong parameters", NULL), STATUS_FAILURE;

    if ((mregion = get_mregion_by_mchunk(marena, used_mchunk, used_mchunk->allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    // We keep as much bound mregions as initialized. Those are expected to be collected by the OS as PAGE FAULTS.
    free_bound_mregion_threshold = INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE;
    is_bound_mregion = IS_BOUND_MREGION(used_mchunk->allocation_size);

    if ((freed_mchunk = free_mchunk(*mregion, used_mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    try_coalesce_with_neighboring_free_mchunks(*mregion, &freed_mchunk);

    if (free_mregion(mregion, is_bound_mregion, free_bound_mregion_threshold) == STATUS_FAILURE)
        return STATUS_FAILURE;
    
    return freed_mchunk;
}