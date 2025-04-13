/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_infer_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:38:05 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:38:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer the size of a `mbin_t`
 * based on the amount of bytes we request to store in a `mchunk_t`.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
 * @note 
*/
size_t  mbin_infer_size(size_t requested_bytes)
{
    if (requested_bytes <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MBIN_SIZE;
    if (requested_bytes <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MBIN_SIZE;
    return LARGE_MBIN_SIZE(requested_bytes);
}
