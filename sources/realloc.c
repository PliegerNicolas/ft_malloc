/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:26 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *realloc(void *ptr, size_t size)
{
    mregion_t   **mregion;
    mchunk_t    *original_mchunk;
    mchunk_t    *new_mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    if (!ptr)
        return malloc(size);
    else if (size == 0)
        return free(ptr), NULL;

    original_mchunk = GET_MCHUNK_PTR(ptr);
    if (!original_mchunk || mchunk_has_aberrant_values(original_mchunk) || original_mchunk->state != USED)
        return NULL;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, original_mchunk)) == STATUS_FAILURE)
        return NULL;
    
    if (original_mchunk->allocation_size == size) {
        new_mchunk = original_mchunk;
    } else if (size > original_mchunk->allocation_size) {
        new_mchunk = grow_mchunk(*mregion, original_mchunk, size);
    } else {
        new_mchunk = shrink_mchunk(*mregion, original_mchunk, size);
    }

    if (new_mchunk == STATUS_FAILURE)
        return NULL;
    return GET_MCHUNK_DATA_PTR(new_mchunk);
}
