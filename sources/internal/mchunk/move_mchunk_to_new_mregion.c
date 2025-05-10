/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mchunk_to_new_mregion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 21:35:54 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 21:35:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void *copy_data_between_mchunks(mchunk_t *dest, mchunk_t *src)
{
    size_t  bytes_to_move;

    bytes_to_move = (dest->allocation_size > src->allocation_size) ? (src->allocation_size) : (dest->allocation_size);
    return ft_memcpy(GET_MCHUNK_DATA_PTR(dest), GET_MCHUNK_DATA_PTR(src), bytes_to_move);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *move_mchunk_to_new_mregion(mchunk_t *original_mchunk, size_t new_allocation_size)
{
    mchunk_t    *relocated_mchunk;

    if (!original_mchunk)
        return STATUS_FAILURE;

    if ((relocated_mchunk = alloc_mchunk(new_allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    copy_data_between_mchunks(relocated_mchunk, original_mchunk);

    if (free_mchunk(original_mchunk) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return relocated_mchunk;
}
