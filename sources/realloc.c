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
    mchunk_t    *mchunk;
    mchunk_t    *reallocated_mchunk;

    ft_putendl_fd("AAAAAAAAAAAAAAAAAAAAAAAAA", STDOUT_FILENO);

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    if (!ptr)
        return malloc(size);

    mchunk = GET_MCHUNK_PTR(ptr);
    if (!mchunk || mchunk_has_aberrant_values(mchunk) || mchunk->state != USED)
        return NULL;

    if ((reallocated_mchunk = realloc_mchunk(&gmarena, mchunk, size)) == STATUS_FAILURE)
        return NULL;

    if (!reallocated_mchunk)
        return NULL;
    return GET_MCHUNK_DATA_PTR(reallocated_mchunk);
}
