/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_allocation_size_to_marena_mregion_head.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 16:43:15 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 16:43:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Maps allocation size to `marena_t`'s most fitting `mregion_t` head.
 * 
 * @param marena Pointer to given `marena_t` to look inside of.
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @note The returned reference is always defined.
 * 
 * @returns Reference to best fitting `mregion_t` head node.
*/
mregion_t   **map_allocation_size_to_marena_mregion_head(marena_t *marena, size_t allocation_size)
{
    if (allocation_size <= MCHUNK_TINY_MAX_DATA_SIZE)
        return &marena->bound_mregions[TINY_MREGION];
    if (allocation_size <= MCHUNK_SMALL_MAX_DATA_SIZE)
        return &marena->bound_mregions[SMALL_MREGION];
    return &marena->unbound_mregion;
}
