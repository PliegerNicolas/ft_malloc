/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_mregion_best_fit_free_mchunk.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 10:00:23 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-04 10:00:23 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  has_free_mchunks(mregion_t *mregion)
{
    return mregion->mbin != NULL;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    **get_or_create_mregion_best_fit_free_mchunk(mregion_t **mregion_head, size_t allocation_size)
{
    mregion_t   **current_mregion;
    mchunk_t    **best_fit_free_mchunk;

    if (!mregion_head)
        return STATUS_FAILURE;

    current_mregion = mregion_head;
    while (*current_mregion)
    {
        if (has_free_mchunks(*current_mregion))
            if ((best_fit_free_mchunk = find_best_fit_free_mchunk(current_mregion, allocation_size)) != NULL)
                return best_fit_free_mchunk;

        current_mregion = &(*current_mregion)->next;
    }

    if (!*current_mregion && init_mregion(current_mregion, allocation_size) == STATUS_FAILURE)
        return STATUS_FAILURE;
    best_fit_free_mchunk = &(*current_mregion)->mbin;

    return best_fit_free_mchunk;
}
