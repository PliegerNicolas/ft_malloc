/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:07:09 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:07:09 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static mbin_t   *mmap_mbin(size_t mmap_size)
{
    mbin_t          *mbin;
    struct rlimit   rlimit;

    // getrlimit should almost never fail.
    if (getrlimit(RLIMIT_AS, &rlimit) == -1)
        return FAILURE;
    
    // Exists for potential more precise error handling.
    if (rlimit.rlim_cur != RLIM_INFINITY && mmap_size > rlimit.rlim_cur)
        return FAILURE;

    mbin = mmap(NULL, mmap_size, MMAP_PROTECTIONS, MMAP_FLAGS, -1, 0);
    if (mbin == MAP_FAILED)
        return FAILURE;

    return mbin;
}

/**
 * @brief Creates a `mbin_t*` node with default values.
 * Partitionned in `mchunk_t*`s.
 * @param requested_data_size  Amount of bytes a contained `mchunk_t *`
 * should hold.
 * 
 * @return The first node of a `mbin_t*` doubly-linked-list.
*/
mbin_t  *mbin_create(size_t requested_data_size)
{
    mbin_t  *mbin;
    size_t  padded_mbin_size;
    size_t  target_mchunk_size;

    if (requested_data_size == 0)
        return NULL;

    padded_mbin_size = mbin_infer_size(requested_data_size);
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

    target_mchunk_size = mchunk_infer_size_by_storage_size(requested_data_size);
    mbin_partition(mbin, target_mchunk_size);

    return mbin;
}
