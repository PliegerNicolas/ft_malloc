/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_create_next.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:25:50 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:25:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Appends a new `mchunk_t*` contiguously in memory after the given one,
 * provided its `size` is at least twice the given `target_mchunk_size`.
 * 
 * @param target_mchunk_size Number of bytes that the new `mchunk_t*` is
 * expected to hold.
 * @note If condition isn't met, NULL si returnned and he given `mchunk_t**`
 * remains unchanged.
*/
mchunk_t *mchunk_create_next(mchunk_t **mchunk, size_t target_mchunk_size)
{
    mchunk_t    *current_mchunk;
    mchunk_t    *next_mchunk;

    if (!mchunk || !*mchunk)
        return NULL;

    current_mchunk = *mchunk;

    if (current_mchunk->size < 2 * target_mchunk_size)
        return NULL;

    next_mchunk = (mchunk_t *)((unsigned char *)current_mchunk + target_mchunk_size);
    *next_mchunk = (mchunk_t) {
        .state = FREE,
        .size = current_mchunk->size - target_mchunk_size,
        .prev_size = target_mchunk_size,
        .requested_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = current_mchunk,
    };

    current_mchunk->size = target_mchunk_size;
    current_mchunk->next_free_mchunk = next_mchunk;

    return next_mchunk;
}