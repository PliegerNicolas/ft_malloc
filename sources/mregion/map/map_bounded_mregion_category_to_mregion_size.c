/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bounded_mregion_category_to_mregion_size.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 10:18:53 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 10:18:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  map_bounded_mregion_category_to_mregion_size(bounded_mregion_category_t category)
{
    switch (category)
    {
        case TINY_MREGION:
            return map_allocation_size_to_mregion_size(MCHUNK_TINY_MAX_DATA_SIZE);
        case SMALL_MREGION:
            return map_allocation_size_to_mregion_size(MCHUNK_SMALL_MAX_DATA_SIZE);
        default:
            return 0;
    }
}
