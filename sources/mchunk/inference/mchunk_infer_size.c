/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_infer_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:40:10 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:40:10 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer a `MCHUNK_SIZE` based on a given data size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t  mchunk_infer_size_by_storage_size(size_t requested_bytes)
{
    if (requested_bytes <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MCHUNK_SIZE;
    else if (requested_bytes <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MCHUNK_SIZE;
    else
        return LARGE_MCHUNK_SIZE(requested_bytes);
}

/** 
 * @brief Infer a `MCHUNK_SIZE` based on a given `mbin_subcategory_t` and/or size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t  mchunk_infer_size_by_mbin_subcategory(mbin_subcategory_t subcategory, size_t requested_bytes)
{
    switch(subcategory)
    {
        case MBIN_TINY:
            return TINY_MCHUNK_SIZE;
        case MBIN_SMALL:
            return SMALL_MCHUNK_SIZE;
        case MBIN_LARGE:
            return LARGE_MCHUNK_SIZE(requested_bytes);
        default:
            return 0;
    };
}
