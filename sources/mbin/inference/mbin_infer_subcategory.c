/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_infer_subcategory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:39:11 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:39:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer a `mbin_subcategory_t` based on size of storable data in `mchunk_t`.
 * 
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
mbin_subcategory_t  mbin_infer_subcategory(size_t requested_bytes)
{
    if (requested_bytes < TINY_MCHUNK_DATA_SIZE)
        return MBIN_TINY;
    else if (requested_bytes < SMALL_MCHUNK_DATA_SIZE)
        return MBIN_SMALL;
    else
        return MBIN_LARGE;
}
