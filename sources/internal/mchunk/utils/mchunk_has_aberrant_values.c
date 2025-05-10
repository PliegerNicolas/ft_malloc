/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_has_aberrant_values.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:49:04 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:49:04 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    mchunk_has_aberrant_values(mchunk_t *mchunk)
{
    size_t  max_allocation_size = get_max_allocation_size(0);

    if (!mchunk)
        return false;

    if (!IS_ALIGNED(mchunk, ALIGNMENT_BOUNDARY))
        return printerr("mchunk_has_aberrant_values()", "misaligned mchunk detected", mchunk), true;

    // TODO: Handle double free.
    // return printerr("mchunk_has_aberrant_values()", "double free or corrupted mchunk", mchunk), true;

    if (mchunk->allocation_size > max_allocation_size || mchunk->prev_allocation_size > max_allocation_size)
        return printerr("mchunk_has_aberrant_values()", "corrupted mchunk", mchunk), true;

    if (!(mchunk->state >= 0 && mchunk->state < NUM_USAGE_STATES))
        return printerr("mchunk_has_aberrant_values()", "corrupted mchunk", mchunk), true;

    return false;
}
