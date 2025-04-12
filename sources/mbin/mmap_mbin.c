/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_mbin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 20:18:56 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 20:18:56 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mbin_t  *mmap_mbin(size_t mmap_size)
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
};