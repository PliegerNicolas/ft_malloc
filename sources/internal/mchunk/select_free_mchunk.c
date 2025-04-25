/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_free_mchunk.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-22 21:42:44 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-22 21:42:44 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
static void iterate_to_best_fit_mregion(mregion_t **mregion)
{
    mregion_t   *current_mregion;

    if (!mregion)
        return;

    current_mregion = *mregion;
    while (current_mregion && current_mregion->mbin == NULL)
        current_mregion = current_mregion->next;
    *mregion = current_mregion;
}

/**
 * @brief ...
*/
mchunk_t    *select_free_mchunk(marena_t *gmarena, size_t allocation_size)
{
    mregion_t   *mregion_head;
    mregion_t   *current_mregion;
    mchunk_t    *free_mchunk;

    if (!gmarena)
        return STATUS_FAILURE;
    
    mregion_head = find_marena_best_fit_mregion_head(gmarena, allocation_size);
    if (mregion_head == STATUS_FAILURE)
        return STATUS_FAILURE;
       
    current_mregion = mregion_head;
    while (current_mregion)
    {
        iterate_to_best_fit_mregion(&current_mregion);
        free_mchunk = find_best_fit_free_mchunk(&current_mregion->mbin, allocation_size);

        if (free_mchunk)
            return free_mchunk;

        if (free_mchunk == STATUS_FAILURE)
            return STATUS_FAILURE;

        if (!current_mregion->next && init_mregion(&current_mregion->next, map_allocation_size_to_mregion_size(allocation_size)))
            return STATUS_FAILURE;

        current_mregion = current_mregion->next;
    }

    return STATUS_FAILURE;
}