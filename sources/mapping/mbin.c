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
