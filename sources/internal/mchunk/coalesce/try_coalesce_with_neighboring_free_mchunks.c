/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_coalesce_with_neighboring_free_mchunks.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 22:24:52 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 22:24:52 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    try_coalesce_with_neighboring_free_mchunks(mregion_t *mregion, mchunk_t **mchunk)
{
    mchunk_t    *prev_mchunk;
    size_t      prev_allocation_size;

    if (!mregion || !mchunk || !*mchunk)
        return;

    try_coalesce_with_next_free_mchunk(mregion, *mchunk);

    prev_mchunk = (*mchunk)->prev_free_mchunk;
    if (!prev_mchunk)
        return;

    prev_allocation_size = prev_mchunk->allocation_size;
    try_coalesce_with_next_free_mchunk(mregion, prev_mchunk);
    if (prev_mchunk->allocation_size > prev_allocation_size)
        *mchunk = prev_mchunk;
}
