/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_categories.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 16:00:26 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 16:00:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
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

/**
 * @brief ...
*/
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

/**
 * @brief
 */
char  *get_mbin_subcategory_name(size_t mbin_size)
{
    if (mbin_size <= TINY_MBIN_SIZE)
        return "TINY";
    if (mbin_size <= SMALL_MBIN_SIZE)
        return "SMALL";
    return "LARGE";
}