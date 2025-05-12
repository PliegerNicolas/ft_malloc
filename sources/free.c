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
    if (!mchunk || mchunk_has_aberrant_values(mchunk) || mchunk->state != USED)
        return;

    if ((freed_mchunk = free_mchunk_or_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return;

    return;
}
