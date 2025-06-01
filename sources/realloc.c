/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:24:17 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:24:17 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *realloc(void *ptr, size_t size)
{
    marena_t    *marena;
    mchunk_t    *mchunk;
    mchunk_t    *reallocated_mchunk;

    if (!ptr)
        return malloc(size);
    else if (size == 0)
        return free(ptr), NULL;

    if ((marena = init_gmarena_once()) == STATUS_FAILURE)
        return NULL;

    if (has_allocation_size_aberrant_value(size))
        return NULL;

    mchunk = GET_MCHUNK_PTR(ptr);
    if (!mchunk || has_mchunk_aberrant_values(mchunk) || mchunk->state != USED)
        return NULL;

    if (gmutex_lock() == STATUS_FAILURE)
        return NULL;
    if ((reallocated_mchunk = realloc_mchunk(&gmarena, mchunk, size)) == STATUS_FAILURE)
        return gmutex_unlock(), NULL;
    gmutex_unlock();

    return GET_MCHUNK_DATA_PTR(reallocated_mchunk);
}
