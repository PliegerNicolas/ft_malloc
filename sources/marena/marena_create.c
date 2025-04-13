/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marena_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:35 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Create and initializes to default values a new `marena_t`.
 * 
 * @return A `marena_t`.
 * The value of the parameter `status` is set to `SUCCESS` if initialization succeeded,
 * or `FAILURE` if it failed.
*/
marena_t    marena_create(status_t *status)
{
    marena_t    marena;
    mbin_t      *mbins;

    ft_bzero(marena.uniform_mbins, sizeof(marena.uniform_mbins));
    ft_bzero(marena.non_uniform_mbins, sizeof(marena.non_uniform_mbins));

    for (mbin_subcategory_t c = 0; c < NUM_UNIFORM_MBINS; c++)
    {
        marena.uniform_mbins[c] = mbins_create(c, TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY);
        if (marena.uniform_mbins[c] == FAILURE)
            return (*status = FAILURE, marena);
    }

    for (mbin_subcategory_t c = 0; c < NUM_NON_UNIFORM_MBINS; c++)
    {
        marena.non_uniform_mbins[c] = mbins_create(c, 0);
        if (marena.non_uniform_mbins[c] == FAILURE)
            return (*status = FAILURE, marena);
    }

    return (*status = SUCCESS, marena);
}
