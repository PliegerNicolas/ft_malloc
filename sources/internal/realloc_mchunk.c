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

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *realloc_mchunk(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size)
{
    if (!mchunk)
        return STATUS_FAILURE;

    return NULL;
}

// mregion_t   **mregion;
// mchunk_t    *freed_mchunk;

// if (!used_mchunk || used_mchunk->state != USED)
//     return STATUS_FAILURE;

// if ((mregion = get_mregion_by_mchunk(marena, used_mchunk, used_mchunk->allocation_size)) == STATUS_FAILURE)
//     return STATUS_FAILURE;

// if ((freed_mchunk = free_mchunk(*mregion, used_mchunk)) == STATUS_FAILURE)
//     return STATUS_FAILURE;

// if ((freed_mchunk = try_coalescing_with_neighbors(*mregion, freed_mchunk)) == STATUS_FAILURE)
//     return STATUS_FAILURE;

// if ((*mregion)->used_mchunks == 0 && free_mregion(mregion) == STATUS_FAILURE)
//     return STATUS_FAILURE;

// return freed_mchunk;