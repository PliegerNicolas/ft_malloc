/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-06 17:28:12 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-06 17:28:12 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

// static bool is_mregion_used(mregion_t *mregion)
// {
//     mchunk_t        *current_mchunk;
//     mchunk_t        *current_free_mchunk;
//     unsigned char   *mregion_right_data_boundary;

//     if (!mregion)
//         return false;

//     mregion_right_data_boundary = (unsigned char *)mregion + mregion->size;

//     current_mchunk = GET_MREGION_FIRST_MCHUNK(mregion);
//     current_free_mchunk = mregion->mbin;

//     while (current_mchunk && (unsigned char *)current_mchunk < mregion_right_data_boundary)
//     {
//         if (current_mchunk != current_free_mchunk)
//             return true;

//         current_mchunk = GET_NEXT_MCHUNK(current_mchunk);
//         current_free_mchunk = current_free_mchunk->next_free_mchunk;
//     }

//     return false;
// }

static inline bool  is_mregion_used(mregion_t *mregion)
{
    return mregion->used_mchunks != 0;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    free_mregion(mregion_t **mregion)
{
    mregion_t   *next_mregion;
    mregion_t   *current_mregion;
    mregion_t   *prev_mregion;

    if (!mregion || !*mregion)
        return STATUS_FAILURE;

    if (is_mregion_used(*mregion))
        return STATUS_SUCCESS;

    current_mregion = *mregion;
    next_mregion = current_mregion->next;
    prev_mregion = current_mregion->prev;

    if (next_mregion)
        next_mregion->prev = prev_mregion;

    if (prev_mregion)
    {
        prev_mregion->next = next_mregion;
        *mregion = prev_mregion;
    }
    else
        *mregion = next_mregion;


    if (munmap(current_mregion, current_mregion->size) == -1)
        return STATUS_FAILURE;

    return STATUS_SUCCESS;
}
