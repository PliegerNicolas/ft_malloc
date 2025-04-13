/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:10:19 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:10:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Partitions the memory held by the given `mbin_t *`
 * into `mchunk_t *`s of a given size in bytes.
 * @param mbin A `mbin_t *` with `->start` holding the total potential
 * held memory in bytes.
 * @param target_mchunk_size Bytes each `mchunk_t` should be able to hold.
 * 
 * @note Does nothing if `mbin` or `mbin->start` are NULL.
*/
void    mbin_partition(mbin_t *mbin, size_t target_mchunk_size)
{
    mchunk_t    *current_mchunk;
    mchunk_t    *next_mchunk;

    if (!mbin || !mbin->start)
        return;

    current_mchunk = mbin->start;
    while (current_mchunk->size >= 2 * target_mchunk_size)
    {
        next_mchunk = mchunk_create_next(&current_mchunk, target_mchunk_size);
        current_mchunk = next_mchunk;
    }
}