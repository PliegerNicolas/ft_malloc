/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_coalesce_until_allocation_size_reached.c       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 21:28:32 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 21:28:32 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static inline bool  has_mchunk_grown(mchunk_t *mchunk, size_t prev_allocation_size)
{
    return mchunk->allocation_size > prev_allocation_size;
}

static inline bool  has_mchunk_reached_target_size(mchunk_t *mchunk, size_t target_size)
{
    return mchunk->allocation_size >= target_size;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */


bool    try_coalesce_until_allocation_size_reached(mregion_t *mregion, mchunk_t **mchunk, size_t target_size)
{
    size_t  prev_mchunk_allocation_size;

    if (!mregion || !mchunk || !*mchunk)
        return false;

    if (has_mchunk_reached_target_size(*mchunk, target_size))
        return true;

    do
    {
        prev_mchunk_allocation_size = (*mchunk)->allocation_size;
        try_coalesce_with_next_free_mchunk(mregion, mchunk);
    }
    while (has_mchunk_grown(*mchunk, prev_mchunk_allocation_size) && has_mchunk_reached_target_size(*mchunk, target_size));

    return true;
}
