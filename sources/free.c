/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:24:04 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:24:04 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    free(void *ptr)
{
    marena_t    *marena;
    mregion_t   **mregion;
    mchunk_t    *mchunk, *freed_mchunk;

    if (!ptr)
        return;

    if (gmutex_lock() == STATUS_FAILURE)
        return;
    if ((marena = init_gmarena_once()) == STATUS_FAILURE)
        return (void)gmutex_unlock();

    mchunk = GET_MCHUNK_PTR(ptr);
    if (!mchunk || (mregion = get_mregion_by_mchunk(marena, mchunk, 0)) == STATUS_FAILURE)
        return gmutex_unlock(), printerr("free()", "double free or corruption", mchunk);

    if (!mchunk || has_mchunk_aberrant_values(mchunk))
        return (void)gmutex_unlock();
    else if (mchunk->state != USED)
        return gmutex_unlock(), printerr("free()", "double free or corruption", mchunk);

    if ((freed_mchunk = free_mchunk_or_mregion(&gmarena, mregion, mchunk)) == STATUS_FAILURE)
        return (void)gmutex_unlock();
    gmutex_unlock();

    return;
}
