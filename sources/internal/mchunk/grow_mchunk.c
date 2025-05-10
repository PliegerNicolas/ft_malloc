/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 21:06:25 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-09 21:06:25 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *grow_mchunk(mregion_t *mregion, mchunk_t *mchunk, size_t new_allocation_size)
{
    if (!mchunk)
        return STATUS_FAILURE;

    if (mchunk->allocation_size <= new_allocation_size)
        return STATUS_FAILURE;

    return mchunk;
}
