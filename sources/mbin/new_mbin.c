/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mbin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 14:52:14 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-10 14:52:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Create a new `mbin_t` and initialises it's first `mchunk_t`.
 * 
 * @param requested_data_size Expected bytes that can be held per `mchunk_t`.
 * `mbin_t`s size is deduced from it.
 * 
 * @note `mbin_t`s size is equivalent to the bytes requested to mmap().
*/
mbin_t  *new_mbin(size_t requested_data_size)
{
    mbin_t  *mbin;
    size_t  padded_mbin_size;
    size_t  target_mchunk_size;

    if (requested_data_size == 0)
        return NULL;

    padded_mbin_size = get_mbin_size(requested_data_size);
    mbin = mmap_mbin(padded_mbin_size);
    if (mbin == MAP_FAILED)
        return FAILURE;

    *mbin = (mbin_t) {
        .size = padded_mbin_size,
        .start = MBIN_INITIAL_MCHUNK_PTR(mbin),
        .next = NULL,
        .prev = NULL,
    };

    *mbin->start = (mchunk_t) {
        .state = FREE,
        .size = MBIN_INITIAL_MCHUNK_SIZE(mbin),
        .prev_size = 0,
        .requested_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    target_mchunk_size = get_mchunk_size(requested_data_size);
    mchunkify_mbin(&mbin->start, target_mchunk_size);

    return mbin;
};
