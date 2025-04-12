/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_marena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 19:25:01 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 19:25:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Clear an existing `marena_t`.
 * @note Deallocate its content and resets its internal state.
*/
void    clear_marena(marena_t *marena)
{
    for (mbin_subcategory_t c = 0; c < NUM_UNIFORM_MBINS; c++)
        if (marena->uniform_mbins[c])
            clear_mbin(&marena->uniform_mbins[c]);

    for (mbin_subcategory_t c = 0; c < NUM_NON_UNIFORM_MBINS; c++)
        if (marena->non_uniform_mbins[c])
            clear_mbin(&marena->non_uniform_mbins[c]);
}
