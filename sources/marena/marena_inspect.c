/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_marena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 23:19:11 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 23:19:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Displays a human-readable representation of the allocated memory zones
 * in the given `marena_t*` on the specified file descriptor.
 *
 * @note Does nothing if the marena is NULL.
*/
size_t  marena_inspect(marena_t *marena, int fd)
{
    size_t  total_size = 0;

    if (!marena)
        return 0;

    for (mbin_subcategory_t c = 0; c < NUM_UNIFORM_MBINS; c++)
        total_size += mbin_inspect(&marena->uniform_mbins[c], fd);

    for (mbin_subcategory_t c = 0; c < NUM_NON_UNIFORM_MBINS; c++)
        total_size += mbin_inspect(&marena->non_uniform_mbins[c], fd);

    return total_size;
}
