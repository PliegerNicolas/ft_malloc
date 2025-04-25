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

/**
 * @brief Map allocation size to expected `mregion_t` size.
 * 
 * @param marena Pointer to given `marena_t` to look inside of.
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @returns Best fitting `PAGE_SIZE` aligned `mregion_t` size in bytes.
*/
size_t  map_allocation_size_to_mregion_size(size_t allocation_size)
{
    size_t  mchunk_data_size;
    size_t  total_mchunks;

    if (allocation_size <= MCHUNK_TINY_MAX_DATA_SIZE)
    {
        mchunk_data_size = MCHUNK_TINY_MAX_DATA_SIZE;
        total_mchunks = MIN_MCHUNKS_PER_BOUND_MREGION;
    }
    else if(allocation_size <= MCHUNK_SMALL_MAX_DATA_SIZE)
    {
        mchunk_data_size = MCHUNK_SMALL_MAX_DATA_SIZE;
        total_mchunks = MIN_MCHUNKS_PER_BOUND_MREGION;
    }
    else
    {
        mchunk_data_size = allocation_size;
        total_mchunks = 1;
    }

    return ALIGN_UP(MREGION_HEADER_PADDED_SIZE + (total_mchunks * mchunk_data_size), PAGE_SIZE);
}
