/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mregion_by_mchunk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 03:30:29 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 03:30:29 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static mregion_t    **find_mregion_containing_mchunk(mregion_t **mregion_head, mchunk_t *mchunk)
{
    mregion_t   **current_mregion;

    current_mregion = mregion_head;
    while (*current_mregion)
    {
        if (does_mregion_contain_mchunk(*current_mregion, mchunk))
            return current_mregion;
        current_mregion = &(*current_mregion)->next;
    }

    return NULL;
}

mregion_t   **get_mregion_by_mchunk(marena_t *marena, mchunk_t *mchunk, size_t allocation_size)
{
    mregion_t   **mregion_head;
    mregion_t   **mregion;

    if (!marena || !mchunk)
        return printerr("get_mregion_by_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    if ((mregion_head = map_allocation_size_to_marena_mregion_head(marena, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    // allocation_size is only a hint: an mchunk can outgrow its size class (cf. grow_mchunk()).
    if ((mregion = find_mregion_containing_mchunk(mregion_head, mchunk)))
        return mregion;

    for (bound_mregion_type_t type = 0; type < NUM_BOUND_MREGION_TYPES; type++)
        if ((mregion = find_mregion_containing_mchunk(&marena->bound_mregions[type], mchunk)))
            return mregion;
    if ((mregion = find_mregion_containing_mchunk(&marena->unbound_mregion, mchunk)))
        return mregion;

    return STATUS_FAILURE;
}
