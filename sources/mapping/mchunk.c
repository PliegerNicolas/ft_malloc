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
 * @brief Infer a `MCHUNK_SIZE` based on a given data size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t  get_mchunk_size(size_t requested_bytes)
{
    if (requested_bytes <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MCHUNK_SIZE;
    else if (requested_bytes <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MCHUNK_SIZE;
    else
        return LARGE_MCHUNK_SIZE(requested_bytes);
}

/**
 * @brief Infer a `MCHUNK_SIZE` based on a given `mchunk_t*`.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t   get_mchunk_data_size(mchunk_t *mchunk)
{
    return GET_MCHUNK_DATA_SIZE(mchunk);
}
