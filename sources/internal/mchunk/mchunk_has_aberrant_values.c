/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_has_aberrant_values.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 12:29:21 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-05 12:29:21 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    mchunk_has_aberrant_values(mchunk_t *mchunk)
{
    size_t  max_allocation_size;

    max_allocation_size = get_max_allocation_size(0);

    if (!IS_ALIGNED(mchunk, ALIGNMENT_BOUNDARY))
        return true;

    if (mchunk->allocation_size > max_allocation_size)
        return true;

    if (mchunk->prev_allocation_size > max_allocation_size)
        return true;

    if (!(mchunk->state >= 0 && mchunk->state < NUM_USAGE_STATES))
        return true;

    return false;
}
