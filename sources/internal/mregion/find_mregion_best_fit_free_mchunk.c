/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_mregion_best_fit_free_mchunk.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 21:46:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 21:46:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Find the best fitting `mchunk_t` from a `mregion_t`.
 * Adds a new `mregion_t` to the linked-list if needed.
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @returns The best fitting `mchunk_t`.
 * Or `STATUS_FAILURE`.
*/
mchunk_t    *find_mregion_best_fit_free_mchunk(mregion_t **mregion, size_t allocation_size)
{
    mregion_t   *current_mregion, *prev_mregion;
    mchunk_t    *best_fit_free_mchunk;

    if (!mregion)
        return STATUS_FAILURE;

    current_mregion = *mregion;
    prev_mregion = NULL;
    while (current_mregion)
    {
        if (current_mregion->mbin != NULL)
        {
            best_fit_free_mchunk = find_mbin_best_fit_free_mchunk(&current_mregion->mbin, allocation_size);
            if (best_fit_free_mchunk)
                return best_fit_free_mchunk;
        }

        prev_mregion = current_mregion;
        current_mregion = current_mregion->next;
    }

    // Create a new `mregion_t`, ensuring it's mbin is totally free and can contain allocation_size.
    if (init_mregion(&prev_mregion->next, map_allocation_size_to_mregion_size(allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    current_mregion = prev_mregion->next;

    return current_mregion->mbin;
}