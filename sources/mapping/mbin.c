/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:23:39 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 18:23:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  get_mbin_size(size_t mchunk_data_size)
{
    if (mchunk_data_size <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MBIN_SIZE;
    if (mchunk_data_size <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MBIN_SIZE;
    return LARGE_MBIN_SIZE(mchunk_data_size);
}

size_t  get_mchunk_data_size_per_mbin_uniform_subcategory(mbin_uniform_subcategory_t subcategory)
{
    switch(subcategory)
    {
        case MBIN_TINY:
            return TINY_MCHUNK_DATA_SIZE;
        case MBIN_SMALL:
            return SMALL_MCHUNK_DATA_SIZE;
        default:
            return 0;
    };
}

size_t  get_mchunk_data_size_per_mbin_non_uniform_subcategory(mbin_non_uniform_subcategory_t subcategory, size_t mchunk_data_size)
{
    switch(subcategory)
    {
        case MBIN_LARGE:
            return LARGE_MCHUNK_DATA_SIZE(mchunk_data_size);
        default:
            return 0;
    };
}