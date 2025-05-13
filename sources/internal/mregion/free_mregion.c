/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 13:32:42 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 13:32:42 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  is_mregion_used(mregion_t *mregion)
{
    return mregion->used_mchunks > 0;
}

static bool should_keep_mregion(mregion_t *mregion, bool is_bound_mregion, size_t free_bound_mregion_threshold)
{
    mregion_t   *current_mregion;
    size_t      total_neighboring_mregions;

    if (!mregion || !is_bound_mregion)
        return false;

    total_neighboring_mregions = 0;
    current_mregion = mregion;
    while (current_mregion && current_mregion->prev && total_neighboring_mregions < free_bound_mregion_threshold)
    {
        ++total_neighboring_mregions;
        current_mregion = current_mregion->prev;
    }

    current_mregion = mregion;
    while (current_mregion && current_mregion->next && total_neighboring_mregions < free_bound_mregion_threshold)
    {
        ++total_neighboring_mregions;
        current_mregion = current_mregion->next;
    }

    return total_neighboring_mregions < free_bound_mregion_threshold;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    free_mregion(mregion_t **mregion, bool is_bound_mregion, size_t free_bound_mregion_threshold)
{
    mregion_t   *curr_mregion;

    if (!mregion || !*mregion)
        return printerr("free_mregion()", "Wrong parameters", NULL), STATUS_FAILURE;
    
    if (is_mregion_used(*mregion) || should_keep_mregion(*mregion, is_bound_mregion, free_bound_mregion_threshold))
        return STATUS_SUCCESS;

    curr_mregion = *mregion;

    if (curr_mregion->next)
        curr_mregion->next->prev = curr_mregion->prev;
    if (curr_mregion->prev)
        curr_mregion->prev = curr_mregion->next;

    *mregion = curr_mregion->prev ? curr_mregion->prev : curr_mregion->next;

    if (munmap_mregion(&curr_mregion) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return STATUS_SUCCESS;
}
