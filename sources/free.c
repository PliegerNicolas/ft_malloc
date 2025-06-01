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
    mchunk_t    *mchunk, *freed_mchunk;

    if ((marena = init_gmarena_once()) == STATUS_FAILURE)
        return;

    if (!ptr)
        return;

    mchunk = GET_MCHUNK_PTR(ptr);
    if (!mchunk || !is_mchunk_in_marena(marena, mchunk))
        return printerr("free()", "double free or corruption", mchunk);

    if (!mchunk || has_mchunk_aberrant_values(mchunk))
        return;
    else if (mchunk->state != USED)
        return printerr("free()", "double free or corruption", mchunk);

    if (gmutex_lock() == STATUS_FAILURE)
        return;
    if ((freed_mchunk = free_mchunk_or_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return (void)gmutex_unlock();
    gmutex_unlock();

    return;
}
