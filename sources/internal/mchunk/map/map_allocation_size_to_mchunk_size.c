/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_size_to_mchunk_size.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 10:16:39 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 10:16:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Maps an allocation_size to it's expected full `mchunk_t` size (metadata + data + padding).
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @returns Best fitting `ALIGNMENT_BOUNDARY` aligned `mchunk_t` size in bytes.
*/
size_t  map_allocation_size_to_mchunk_size(size_t allocation_size)
{
    return MCHUNK_HEADER_PADDED_SIZE + ALIGN_UP(allocation_size, ALIGNMENT_BOUNDARY);
}
