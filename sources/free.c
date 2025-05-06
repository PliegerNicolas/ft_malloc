/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:19 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:19 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    free(void *ptr)
{
    mregion_t   **mregion;
    mchunk_t    *mchunk;

    if (!ptr)
        return;

    mchunk = GET_MCHUNK_PTR(ptr);
    if (!mchunk || mchunk_has_aberrant_values(mchunk))
        return;

    if (mchunk->state != USED)
        return;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return;

    if (free_mchunk(*mregion, mchunk) == STATUS_FAILURE)
        return;
    (*mregion)->used_mchunks -= 1;

    if (free_mregion(mregion) == STATUS_FAILURE)
        return;
}
