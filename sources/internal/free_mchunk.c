/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 16:30:08 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 16:30:08 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

status_t    free_mchunk(mchunk_t *mchunk)
{
    mregion_t   **mregion;

    if (!mchunk || mchunk->state != USED)
        return STATUS_FAILURE;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    
    mchunk->state = FREE;
    insert_free_mchunk_in_mregion_mbin(*mregion, mchunk);
    (*mregion)->used_mchunks -= 1;

    coalesce_with_next_free_mchunks(mchunk, mchunk->next_free_mchunk);
    coalesce_with_prev_free_mchunks(&mchunk, mchunk->prev_free_mchunk);

    if (free_mregion(mregion) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return STATUS_SUCCESS;
}
