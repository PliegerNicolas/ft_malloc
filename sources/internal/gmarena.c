/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gmarena.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 14:11:50 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 14:11:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Declaration of global variable `marena_t`.
 * It represents the current thread's internal heap state.
*/
marena_t    gmarena;

/**
 * @brief Initializes the global `marena_t` instance in a singleton-like pattern.
 * 
 * Given `NUM_INITIAL_BOUND_MREGIONS_PER_CATEGORY` some bound `mregion_t`s
 * might immediately be initialized.
 * 
 * @returns Operation related `status_t`.
*/
status_t    init_gmarena_once()
{
    return init_marena_once(&gmarena, NUM_INITIAL_BOUND_MREGIONS_PER_CATEGORY);
}