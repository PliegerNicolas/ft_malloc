/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_size_to_mregion_head.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 22:04:31 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 22:04:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   **map_allocation_size_to_mregion_head(marena_t *marena, size_t allocation_size)
{
    if (allocation_size <= MCHUNK_TINY_MAX_DATA_SIZE)
        return &marena->bounded_mregions[TINY_MREGION];
    if (allocation_size <= MCHUNK_SMALL_MAX_DATA_SIZE)
        return &marena->bounded_mregions[SMALL_MREGION];
    return &marena->unbounded_mregion;
}
