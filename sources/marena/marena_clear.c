/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marena_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:29 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:29 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Deallocates and resets internal state of the given `marena_t*`.
 * 
 * @note Does nothing if marena is NULL.
*/
void    marena_clear(marena_t *marena)
{
    if (!marena)
        return;

    for (mbin_subcategory_t c = 0; c < NUM_UNIFORM_MBINS; c++)
        if (marena->uniform_mbins[c])
            mbin_clear(&marena->uniform_mbins[c]);

    for (mbin_subcategory_t c = 0; c < NUM_NON_UNIFORM_MBINS; c++)
        if (marena->non_uniform_mbins[c])
            mbin_clear(&marena->non_uniform_mbins[c]);
}
