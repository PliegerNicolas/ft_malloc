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

size_t  map_allocation_size_to_mchunk_size(size_t allocation_size)
{
    return MCHUNK_HEADER_PADDED_SIZE + ALIGN_UP(allocation_size, ALIGNMENT_BOUNDARY);
}
