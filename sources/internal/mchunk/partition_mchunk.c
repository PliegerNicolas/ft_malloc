/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_mchunk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 22:14:37 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 22:14:37 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *partition_mchunk(mchunk_t **original_mchunk, size_t allocation_size)
{
    mchunk_t    *leading_mchunk;
    mchunk_t    *remainder_mchunk;
    mchunk_t    cache;

    if (!original_mchunk || !*original_mchunk)
        return printerr("partition_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    cache = **original_mchunk;

    leading_mchunk = *original_mchunk;
    leading_mchunk->allocation_size = allocation_size,
    leading_mchunk->next_free_mchunk = NULL,
    leading_mchunk->prev_free_mchunk = NULL,

    remainder_mchunk = GET_NEXT_MCHUNK(leading_mchunk);
    *remainder_mchunk = (mchunk_t) {
        .state = FREE,
        .allocation_size = ALIGN_UP(cache.allocation_size, ALIGNMENT_BOUNDARY) - GET_MCHUNK_SIZE(leading_mchunk->allocation_size),
        .prev_allocation_size = leading_mchunk->allocation_size,
        .next_free_mchunk = cache.next_free_mchunk,
        .prev_free_mchunk = cache.prev_free_mchunk,
    };

    if (cache.next_free_mchunk)
        cache.next_free_mchunk->prev_free_mchunk = remainder_mchunk;
    if (cache.prev_free_mchunk)
        cache.prev_free_mchunk->next_free_mchunk = remainder_mchunk;

    return (*original_mchunk = remainder_mchunk), leading_mchunk;
}
