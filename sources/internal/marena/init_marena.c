/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_marena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 10:50:06 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 10:50:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Initializes a `marena_t`'s bound `mregion_t`s.
 * @param marena Reference to the pointer of the concerned `marena_t`. `NULL` causes failure.
 * @param initial_mregions_per_bound_category Total bound `mregion_t`s to initialize
 * per `bound_mregion_category_t`.
 * 
 * @returns Operation related `status_t`.
*/
static status_t init_marena_bound_mregions(marena_t **marena, size_t initial_mregions_per_bound_category)
{
    mregion_t   **bound_mregions;
    size_t      mregion_size_per_category;

    if (!marena)
        return STATUS_FAILURE;

    bound_mregions = (*marena)->bound_mregions;

    for (bound_mregion_category_t c = 0; c < NUM_BOUND_MREGIONS_CATEGORIES; c++)
    {
        mregion_size_per_category = map_bound_mregion_category_to_mregion_size(c);
        if (init_mregions(&bound_mregions[c], mregion_size_per_category, initial_mregions_per_bound_category) == STATUS_FAILURE)
            return STATUS_FAILURE;
    }

    return STATUS_SUCCESS;
}

/**
 * @brief Initializes a `marena_t`'s unbound `mregion_t`.
 * @param marena Reference to the pointer of the concerned `marena_t`. `NULL` causes failure.
 * 
 * @returns Operation related `status_t`.
*/
static status_t init_marena_unbound_mregion(marena_t **marena)
{
    mregion_t   *unbound_mregion;

    if (!marena)
        return STATUS_FAILURE;

    unbound_mregion = (*marena)->unbound_mregion;

    unbound_mregion = NULL;
    
    return STATUS_SUCCESS;
}

/**
 * @brief Initializes a given `marena_t`.
 * 
 * @param marena Pointer to the `marena_t` to initialize. `NULL` causes failure.
 * @param initial_mregions_per_bound_category Total bound `mregion_t`s to initialize
 * per `bound_mregion_category_t`.
 * 
 * @returns Operation related `status_t`.
*/
status_t    init_marena(marena_t *marena, size_t initial_mregions_per_bound_category)
{
    if (!marena)
        return STATUS_FAILURE;
    
    ft_bzero(marena->bound_mregions, sizeof(marena->bound_mregions));
    marena->unbound_mregion = NULL;

    if (init_marena_bound_mregions(&marena, initial_mregions_per_bound_category) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if (init_marena_unbound_mregion(&marena) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return STATUS_SUCCESS;
}
