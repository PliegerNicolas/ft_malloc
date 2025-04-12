/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 13:41:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 13:41:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
size_t  show_marena(marena_t *marena, int fd)
{
    size_t  total_size = 0;

    for (mbin_uniform_subcategory_t category = 0; category < NUM_MBIN_UNIFORM_SUBCATEGORIES; category++)
        total_size += show_mbin(&marena->uniform_mbins[category], fd);

    for (mbin_non_uniform_subcategory_t category = 0; category < NUM_MBIN_NON_UNIFORM_SUBCATEGORIES; category++)
        total_size += show_mbin(&marena->non_uniform_mbins[category], fd);

    return total_size;
}