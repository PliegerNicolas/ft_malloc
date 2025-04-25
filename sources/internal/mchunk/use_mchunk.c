/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 22:28:30 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 22:28:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *use_mchunk(mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;
    mchunk_t    *remaining_free_mchunk;
    size_t      used_mchunk_size;
    size_t      remaining_free_mchunk_size;

    if (!free_mchunk)
        return STATUS_FAILURE;

    used_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);
    if (free_mchunk->allocation_size < used_mchunk_size)
        return STATUS_FAILURE;
    remaining_free_mchunk_size = GET_MCHUNK_PADDED_SIZE(free_mchunk) - used_mchunk_size;

    remaining_free_mchunk = (mchunk_t *)(unsigned char *)free_mchunk + used_mchunk_size;
    *remaining_free_mchunk = (mchunk_t) {
        .allocation_size = remaining_free_mchunk_size - MCHUNK_HEADER_PADDED_SIZE,
        .prev_allocation_size = used_mchunk_size - MCHUNK_HEADER_PADDED_SIZE,
        .next_free_mchunk = free_mchunk->next_free_mchunk,
        .prev_free_mchunk = free_mchunk->prev_free_mchunk,
    };

    used_mchunk = free_mchunk;
    *used_mchunk = (mchunk_t) {
        .allocation_size = used_mchunk_size - MCHUNK_HEADER_PADDED_SIZE,
        .prev_allocation_size = free_mchunk->prev_allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    return GET_MCHUNK_DATA_PTR(used_mchunk);
}
