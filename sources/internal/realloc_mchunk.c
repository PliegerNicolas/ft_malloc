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

static bool are_allocation_sizes_mregion_compatible(marena_t *marena, size_t allocation_size1, size_t allocation_size2)
{
    mregion_t **mregion_head1, **mregion_head2;

    if (!marena)
        return false;

    if ((mregion_head1 = map_allocation_size_to_marena_mregion_head(marena, allocation_size1)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    if ((mregion_head2 = map_allocation_size_to_marena_mregion_head(marena, allocation_size2)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return *mregion_head1 == *mregion_head2;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *realloc_mchunk(marena_t *marena, mchunk_t *used_mchunk, size_t reallocation_size)
{
    mchunk_t    *reallocated_mchunk;

    if (!marena || !used_mchunk || used_mchunk->state != USED)
        return printerr("realloc_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (reallocation_size == 0)
        return free_mchunk_or_mregion(marena, used_mchunk), NULL;

    if (!are_allocation_sizes_mregion_compatible(marena, used_mchunk->allocation_size, reallocation_size))
        return migrate_mchunk_to_new_mregion(marena, used_mchunk, reallocation_size);

    if (used_mchunk->allocation_size == reallocation_size)
        reallocated_mchunk = used_mchunk;
    else if (used_mchunk->allocation_size < reallocation_size)
        reallocated_mchunk = grow_mchunk(marena, used_mchunk, reallocation_size);
    else
        reallocated_mchunk = shrink_mchunk(marena, used_mchunk, reallocation_size);

    if (reallocated_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;
    return reallocated_mchunk;
}
