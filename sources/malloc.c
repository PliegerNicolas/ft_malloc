/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:23:36 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:23:36 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *malloc(size_t size)
{
    marena_t    *marena;
    mchunk_t    *allocated_mchunk;

    if ((marena = init_gmarena_once()) == STATUS_FAILURE)
        return NULL;

    if (has_allocation_size_aberrant_value(size))
        return NULL;

    if ((allocated_mchunk = alloc_mchunk(marena, size)) == STATUS_FAILURE)
        return NULL;

    return GET_MCHUNK_DATA_PTR(allocated_mchunk);
}
