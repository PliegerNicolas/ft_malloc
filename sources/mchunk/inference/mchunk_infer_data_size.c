/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_infer_data_size.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:41:39 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:41:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer a `MCHUNK_SIZE` based on a given `mchunk_t*`.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t   mchunk_infer_data_size(mchunk_t *mchunk)
{
    return GET_MCHUNK_DATA_SIZE(mchunk);
}

/**
 * @brief Infer a `MCHUNK_DATA_SIZE` based on a given `mbin_subcategory_t` and/or size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t mchunk_infer_data_size_by_mbin_subcategory(mbin_subcategory_t subcategory, size_t requested_bytes)
{
    switch(subcategory)
    {
        case MBIN_TINY:
            return TINY_MCHUNK_DATA_SIZE;
        case MBIN_SMALL:
            return SMALL_MCHUNK_DATA_SIZE;
        case MBIN_LARGE:
            return LARGE_MCHUNK_DATA_SIZE(requested_bytes);
        default:
            return 0;
    };
}