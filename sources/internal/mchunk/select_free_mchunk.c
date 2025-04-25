// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   select_free_mchunk.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025-04-22 21:42:44 by nicolas           #+#    #+#             */
// /*   Updated: 2025-04-22 21:42:44 by nicolas          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "ft_malloc.h"

// /**
//  * @brief Find the best fitting `mchunk_t` from a mbin.
//  * 
//  * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
//  * 
//  * @note We look for the `mchunk_t with the l
//  * 
//  * @returns The best fitting `mchunk_t` or NULL if not found.
// */
// static mchunk_t *find_mbin_best_fit_mchunk(mchunk_t **mbin, size_t allocation_size)
// {
//     size_t  mchunk_to_use_size;
//     mchunk_t    *best_fit_mchunk;

//     if (!mbin)
//         return NULL;

//     mchunk_to_use_size = map_allocation_size_to_mchunk_size(allocation_size);

//     best_fit_mchunk = NULL;
//     for (mchunk_t *current_mchunk = *mbin; current_mchunk != NULL;current_mchunk = current_mchunk->next_free_mchunk)
//     {
//         if (current_mchunk->allocation_size < mchunk_to_use_size)
//             continue;

//         if (current_mchunk->allocation_size == mchunk_to_use_size)
//             return current_mchunk;

//         if (!best_fit_mchunk || best_fit_mchunk->allocation_size > current_mchunk->allocation_size)
//             best_fit_mchunk = current_mchunk;
//     }

//     return best_fit_mchunk;
// }

/**
 * @brief Iterates through the given `mregion_t` and skips those with empty `->mbin`s.
 * 
 * @param mregion `mregion_t` we want to iterate through. The refered pointer gets altered.
 * 
 * @returns Nothing.
*/
static void skip_mregions_with_empty_mbins(mregion_t **mregion)
{
    if (!mregion)
        return;

    while ((*mregion) && (*mregion)->mbin == NULL)
        (*mregion) = (*mregion)->next;
}

// /**
//  * @brief ...
// */
// static void iterate_to_best_fit_mregion(mregion_t **mregion)
// {
//     mregion_t   *current_mregion;

//     if (!mregion)
//         return;

//     current_mregion = *mregion;
//     while (current_mregion && current_mregion->mbin == NULL)
//         current_mregion = current_mregion->next;
//     *mregion = current_mregion;
// }

// /**
//  * @brief ...
// */
// mchunk_t    *select_free_mchunk(marena_t *gmarena, size_t allocation_size)
// {
//     mregion_t   *mregion_head;
//     mregion_t   *current_mregion;
//     mchunk_t    *free_mchunk;

//     if (!gmarena)
//         return STATUS_FAILURE;
    
//     mregion_head = find_marena_best_fit_mregion_head(gmarena, allocation_size);
//     if (mregion_head == STATUS_FAILURE)
//         return STATUS_FAILURE;
       
//     current_mregion = mregion_head;
//     while (current_mregion)
//     {
//         iterate_to_best_fit_mregion(&current_mregion);
//         free_mchunk = find_best_fit_free_mchunk(&current_mregion->mbin, allocation_size);

//         if (free_mchunk)
//             return free_mchunk;

//         if (free_mchunk == STATUS_FAILURE)
//             return STATUS_FAILURE;

//         if (!current_mregion->next && init_mregion(&current_mregion->next, map_allocation_size_to_mregion_size(allocation_size)))
//             return STATUS_FAILURE;

//         current_mregion = current_mregion->next;
//     }

//     return STATUS_FAILURE;
// }