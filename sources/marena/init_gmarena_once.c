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
 * @brief Declaration of global variable `marena_t`.
 * It represents the current thread's internal heap state.
*/
marena_t    gmarena;

/**
 * @brief Initializes global variable `gmarena` if needed.
 * 
 * @returns `STATUS_SUCCESS` if initialization succeeded or was already initialized.
 * Else `STATUS_FAILURE`.
 * @note Tracks initialization state through internal static boolean.
*/
status_t    init_gmarena_once(marena_t *gmarena, size_t bounded_regions)
{
    static bool is_initialized;

    if (!gmarena)
        return STATUS_FAILURE;
    
    if (is_initialized)
        return STATUS_SUCCESS;

    if (init_marena(gmarena, NUM_INITIAL_BOUNDED_MREGIONS) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return STATUS_SUCCESS;
}
