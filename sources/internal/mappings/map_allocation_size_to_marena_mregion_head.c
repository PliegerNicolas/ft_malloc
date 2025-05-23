/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_size_to_marena_mregion_head.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:18:59 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:18:59 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   **map_allocation_size_to_marena_mregion_head(marena_t *marena, size_t allocation_size)
{
    if (!marena)
        return printerr("map_allocation_size_to_marena_mregion_head()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (allocation_size <= TINY_MCHUNK_MAX_ALLOCATION_SIZE)
        return &(marena->bound_mregions[TINY_MREGION_TYPE]);
    else if (allocation_size <= SMALL_MCHUNK_MAX_ALLOCATION_SIZE)
        return &(marena->bound_mregions[SMALL_MREGION_TYPE]);
    else
        return &(marena->unbound_mregion);
}
