/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-31 03:49:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-31 03:49:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static mbin_t  *mmap_mbin(size_t size)
{
    mbin_t  *ptr = mmap(NULL, size, MMAP_PROTECTIONS, MMAP_FLAGS, -1, 0);

    if (ptr == MAP_FAILED)
        return FAILURE;

    return ptr;
}

mbin_t   *new_mbin(size_t size, enum e_mbin_categories category)
{
    mbin_t      *mbin;
    void        *initial_mchunk;

    if (size < MBIN_METADATA_SIZE)
        return FAILURE;

    mbin = mmap_mbin(size);
    if (mbin == FAILURE)
        return FAILURE;

    switch (category)
    {
        case UNIFORM:
            set_uniform_mbin_initial_mchunk(mbin, size);
            break;
        case IRREGULAR:
            set_irregular_mbin_initial_mchunk(mbin, size);
            break;
        default:
            munmap(mbin, size);
            return FAILURE;
    };

    return mbin;
}
