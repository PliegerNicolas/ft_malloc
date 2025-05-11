/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mregion_bound_type_to_max_allocation_size.c    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:34:08 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:34:08 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  map_mregion_bound_type_to_max_allocation_size(bound_mregion_type_t bound_mregion_type)
{
    switch (bound_mregion_type)
    {
        case TINY_MREGION_TYPE:
            return TINY_MCHUNK_MAX_ALLOCATION_SIZE;
        case SMALL_MREGION_TYPE:
            return SMALL_MCHUNK_MAX_ALLOCATION_SIZE;
        default:
            return 0;
    }
}
