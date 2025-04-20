/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mregion_size_by_allocation_size.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 09:50:59 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 09:50:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  map_allocation_size_to_mregion_size(size_t allocation_size)
{
    if (allocation_size <= MCHUNK_TINY_MAX_DATA_SIZE)
        return ALIGN_UP(MREGION_HEADER_PADDED_SIZE + (MIN_MCHUNKS_PER_BOUNDED_MREGION * (MCHUNK_HEADER_PADDED_SIZE + MCHUNK_TINY_MAX_DATA_SIZE)), PAGE_SIZE);
    if (allocation_size <= MCHUNK_SMALL_MAX_DATA_SIZE)
        return ALIGN_UP(MREGION_HEADER_PADDED_SIZE + (MIN_MCHUNKS_PER_BOUNDED_MREGION * (MCHUNK_HEADER_PADDED_SIZE + MCHUNK_SMALL_MAX_DATA_SIZE)), PAGE_SIZE);
    return ALIGN_UP(MREGION_HEADER_PADDED_SIZE + (MCHUNK_HEADER_PADDED_SIZE + allocation_size), PAGE_SIZE);
}
