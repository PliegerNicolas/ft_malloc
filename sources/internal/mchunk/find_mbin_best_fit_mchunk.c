/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_fit_free_mchunk.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 17:20:28 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 17:20:28 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
static mchunk_t    *find_mbin_mchunk_first_fit(mchunk_t **mbin, size_t allocation_size)
{
    size_t      used_mchunk_size;
    mchunk_t    *current_mchunk;

    if (!mbin)
        return NULL;

    used_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);

    current_mchunk = *mbin;
    while (current_mchunk && current_mchunk->allocation_size < used_mchunk_size)
        current_mchunk = current_mchunk->next_free_mchunk;

    return current_mchunk;
}

/**
 * @brief ...
*/
static mchunk_t    *find_mbin_mchunk_best_fit(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *current_mchunk;
    mchunk_t    *best_fit_mchunk;
    size_t      used_mchunk_size;

    if (!mbin)
        return NULL;

    used_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);

    current_mchunk = *mbin;
    best_fit_mchunk = NULL;
    while (current_mchunk)
    {
        if (current_mchunk->allocation_size == used_mchunk_size)
            return current_mchunk;

        if (!best_fit_mchunk || (current_mchunk->allocation_size < best_fit_mchunk->allocation_size))
            best_fit_mchunk = current_mchunk;

        current_mchunk = current_mchunk->next_free_mchunk;
    }

    return best_fit_mchunk;
}

/**
 * @brief ...
*/
static mchunk_t    *find_mbin_mchunk_good_enough_fit(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *current_mchunk;
    size_t      used_mchunk_size;
    size_t      good_enough_threshold;

    if (!mbin)
        return NULL;

    used_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);
    good_enough_threshold = used_mchunk_size * 1.15;

    current_mchunk = *mbin;
    while (current_mchunk && current_mchunk->allocation_size <= good_enough_threshold)
        current_mchunk = current_mchunk->next_free_mchunk;

    return current_mchunk;
}

/**
 * @brief Find the best fitting `mchunk_t` from a mbin.
 * 
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @note SYK, memory bins only store free `mchunk_t`s.
 * 
 * @returns The best fitting `mchunk_t` or NULL if not found.
*/
mchunk_t    *find_mbin_best_fit_mchunk(mchunk_t **mbin, size_t allocation_size)
{
    // size_t  mchunk_to_use_size;
    // mchunk_t    *current_mchunk;

    // if (!mbin)
    //     return NULL;

    // mchunk_to_use_size = map_allocation_size_to_mchunk_size(allocation_size);

    // current_mchunk = *mbin;
    // while (current_mchunk && current_mchunk->allocation_size < mchunk_to_use_size)
    //     current_mchunk = current_mchunk->next_free_mchunk;

    // return current_mchunk; // mchunk_t or NULL.
}
