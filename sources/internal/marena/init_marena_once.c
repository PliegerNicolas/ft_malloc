/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gmarena_once.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 22:33:05 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 22:33:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Initializes a `marena_t` instance in a singleton-like pattern.
 * 
 * Ensures that only one `marena_t` instance is initialized throughout 
 * the process.
 * 
 * @param marena Reference to the concerned `marena_t`. `NULL` causes failure.
 * @param initial_mregions_per_bound_category Total bound `mregion_t`s to initialize
 * per `bound_mregion_category_t`.
 * 
 * @returns Operation related `status_t`.
*/
status_t    init_marena_once(marena_t *marena, size_t initial_mregions_per_bound_category)
{
    static marena_t *previously_initialized_marena;

    if (!marena)
        return STATUS_FAILURE;

    if (previously_initialized_marena)
    {
        if (previously_initialized_marena != marena)
            return STATUS_FAILURE;
        return STATUS_SUCCESS;
    }

    if (init_marena(marena, initial_mregions_per_bound_category) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return (previously_initialized_marena = marena), STATUS_SUCCESS;
}
