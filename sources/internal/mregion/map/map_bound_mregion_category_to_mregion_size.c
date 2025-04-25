/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bound_mregion_category_to_mregion_size.c       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 12:27:16 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 12:27:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Maps bound `mregion_t` categories to expected `mregion_t` size.
 * 
 * @param category A bound `mregion_t` category (cf. `bound_mregion_category_t`).
 * 
 * @returns Best fitting `PAGE_SIZE` aligned `mregion_t` size in bytes. `0` if category unrecognized.
*/
size_t  map_bound_mregion_category_to_mregion_size(bound_mregion_category_t category)
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
