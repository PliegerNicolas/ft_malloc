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
    mchunk_t    *mchunk;
    mchunk_t    *potentially_relocated_mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    if (!ptr)
        return malloc(size);

    mchunk = GET_MCHUNK_PTR(ptr);
    if (mchunk_has_aberrant_values(mchunk) || mchunk->state != USED)
        return NULL;

    if ((potentially_relocated_mchunk = realloc_mchunk(mchunk, size)) == STATUS_FAILURE)
        return NULL;

    return GET_MCHUNK_DATA_PTR(potentially_relocated_mchunk);
}
