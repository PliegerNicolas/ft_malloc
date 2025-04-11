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

void    clear_marena(marena_t *marena)
{
    for (mbin_uniform_subcategory_t category = 0; category < NUM_MBIN_UNIFORM_SUBCATEGORIES; category++)
    {
        if (marena->uniform_mbins[category])
            clear_mbin(&marena->uniform_mbins[category]);
    };

    for (mbin_non_uniform_subcategory_t category = 0; category < NUM_MBIN_NON_UNIFORM_SUBCATEGORIES; category++)
    {
        if (marena->non_uniform_mbins[category])
            clear_mbin(&marena->non_uniform_mbins[category]);
    };
}