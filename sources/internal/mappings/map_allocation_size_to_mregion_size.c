/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_size_to_mregion_size.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:35:24 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:35:24 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  map_allocation_size_to_mregion_size(size_t allocation_size)
{
    if (allocation_size <= TINY_MCHUNK_MAX_ALLOCATION_SIZE)
        return TINY_MREGION_SIZE;
    else if (allocation_size <= SMALL_MCHUNK_MAX_ALLOCATION_SIZE)
        return SMALL_MREGION_SIZE;
    else
        return LARGE_MREGION_SIZE(allocation_size);
}
