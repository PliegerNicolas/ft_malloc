/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:23:48 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 18:23:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
size_t  get_mchunk_data_size(size_t mchunk_data_size)
{
    if (mchunk_data_size <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MCHUNK_DATA_SIZE;
    if (mchunk_data_size <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MCHUNK_DATA_SIZE;
    return LARGE_MCHUNK_DATA_SIZE(mchunk_data_size);
}

/**
 * @brief ...
*/
size_t  get_mchunk_size(size_t mchunk_data_size)
{
    if (mchunk_data_size <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MCHUNK_SIZE;
    if (mchunk_data_size <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MCHUNK_SIZE;
    return LARGE_MCHUNK_SIZE(mchunk_data_size);
}
