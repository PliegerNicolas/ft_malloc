/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grow_mchunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-09 21:06:25 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-09 21:06:25 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

// mchunk_t    **get_next_mchunk_if_free(mchunk_t *mchunk, mregion_t *related_mregion)
// {
//     unsigned char   *related_mregion_right_data_bound;
//     mchunk_t        *next_free_mchunk;

//     if (!mchunk || !related_mregion)
//         return STATUS_FAILURE;
    
//     related_mregion_right_data_bound = (unsigned char *)related_mregion + related_mregion->size;
//     next_free_mchunk = GET_NEXT_MCHUNK(mchunk);

//     if ((unsigned char *)next_free_mchunk >= related_mregion_right_data_bound)
//         return NULL;
    
//     if (next_free_mchunk->state != FREE)
//         return NULL;

//     return next_free_mchunk;
// }

// static inline bool  is_free_mchunk_mregion_mbin(mchunk_t *free_mchunk, mregion_t *related_mregion)
// {
//     if (!free_mchunk || !related_mregion)
//         return false;
//     return free_mchunk == related_mregion->mbin;
// }

// static mchunk_t *get_and_isolate_next_free_mchunk(mchunk_t *mchunk)
// {
//     mregion_t   **mregion;
//     mchunk_t    *next_mchunk;

//     if (!mchunk)
//         return STATUS_FAILURE;

//     if ((mregion = mchunk_find_corresponding_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
//         return STATUS_FAILURE;

//     next_mchunk = GET_NEXT_MCHUNK(mchunk);
//     if (((unsigned char *)next_mchunk >= (unsigned char *)*mregion + (*mregion)->size)
//         || next_mchunk->state != FREE)
//         return NULL;

//     // Push mregion->mbin forward, to isolate the free_mchunk we are going to use.
//     if (next_mchunk == (*mregion)->mbin)
//     {
//         if ((*mregion)->mbin->next_free_mchunk)
//             (*mregion)->mbin->next_free_mchunk->prev_free_mchunk = NULL;
//         (*mregion)->mbin = (*mregion)->mbin->next_free_mchunk;
//     }

//     return next_mchunk;
// }

static mchunk_t *a(mchunk_t *mchunk)
{
    mregion_t   **mregion;
    mchunk_t    *next_mchunk;

    if (!mchunk)
        return STATUS_FAILURE;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    next_mchunk = GET_NEXT_MCHUNK(mchunk);
    if (!is_mchunk_in_mregion_boundary(*mregion, mchunk))
        return NULL;

    if (next_mchunk->state != FREE)
        return NULL;

    

    return NULL;
}

static inline bool  are_same_mchunks(mchunk_t *mchunk1, mchunk_t *mchunk2)
{
    return mchunk1 == mchunk2;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *grow_mchunk(mchunk_t *original_mchunk, size_t new_allocation_size)
{
    mregion_t   **mregion;
    mchunk_t    *neighboring_mchunk;
    mchunk_t    **neighboring_free_mchunk;

    if (!original_mchunk || new_allocation_size <= original_mchunk->allocation_size)
        return STATUS_FAILURE;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, original_mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    neighboring_mchunk = GET_NEXT_MCHUNK(original_mchunk);
    if (!is_mchunk_in_mregion_boundary(*mregion, neighboring_mchunk) || neighboring_mchunk->state != FREE)
        return move_mchunk_to_new_mregion(original_mchunk, new_allocation_size);
    
    if (are_same_mchunks((*mregion)->mbin, neighboring_mchunk))
        neighboring_free_mchunk = &(*mregion)->mbin;
    else
        neighboring_free_mchunk = &neighboring_mchunk;

    
    return STATUS_FAILURE;
}
