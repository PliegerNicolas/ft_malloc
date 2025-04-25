/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_mbin_best_fit_free_mchunk.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 22:07:14 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 22:07:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/**
 * @brief Find the first `mchunk_t` able to contain `allocation_size` in given mbin.
 * @param mbin Initial `mchunk_t` of free `mchunk_t` list (`mregion_t`->mbin).
 * @param allocation_size Expected amount of bytes to store in requested `mchunk_t`.
 * 
 * @returns First fit free `mchunk_t` or `NULL`.
*/
static mchunk_t    *find_mbin_mchunk_first_fit(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *current_mchunk;
    if (!mbin)
        return NULL;

    current_mchunk = *mbin;
    while(current_mchunk && current_mchunk->allocation_size < allocation_size)
        current_mchunk = current_mchunk->next_free_mchunk;

    return current_mchunk;
}

/**
 * @brief Find the smallest `mchunk_t` able to contain `allocation_size` in given mbin.
 * @param mbin Initial `mchunk_t` of free `mchunk_t` list (`mregion_t`->mbin).
 * @param allocation_size Expected amount of bytes to store in requested `mchunk_t`.
 * 
 * @returns Smallest fit free `mchunk_t` or `NULL`.
*/
static mchunk_t    *find_mbin_mchunk_best_fit(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *best_fit_mchunk;

    if (!mbin)
        return NULL;

    best_fit_mchunk = NULL;
    for (mchunk_t *current_mchunk = *mbin; current_mchunk; current_mchunk = current_mchunk->next_free_mchunk)
    {
        if (current_mchunk->allocation_size < allocation_size)
            continue;

        if (current_mchunk->allocation_size == allocation_size)
            return current_mchunk;

        if (!best_fit_mchunk || (current_mchunk->allocation_size < best_fit_mchunk->allocation_size))
            best_fit_mchunk = current_mchunk;
    }

    return best_fit_mchunk;
}

/**
 * @brief Find the first `mchunk_t` of good enough size able to contain `allocation_size` in given mbin.
 * @param mbin Initial `mchunk_t` of free `mchunk_t` list (`mregion_t`->mbin).
 * @param allocation_size Expected amount of bytes to store in requested `mchunk_t`.
 * 
 * @returns First good enough size fit free `mchunk_t` or `NULL`.
*/
static mchunk_t    *find_mbin_mchunk_good_enough_fit(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *current_mchunk;
    size_t      good_enough_size_threshold;

    if (!mbin)
        return NULL;

    good_enough_size_threshold = allocation_size * 1.15;

    current_mchunk = *mbin;
    while (current_mchunk && current_mchunk->allocation_size < good_enough_size_threshold)
        current_mchunk = current_mchunk->next_free_mchunk;

    return current_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

/**
 * @brief Find the best fitting `mchunk_t` from a mbin.
 * Depending on the `allocation_size` different strategies are employed.
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @note Memory bins only store free `mchunk_t`s.
 * 
 * @returns The best fitting `mchunk_t` or NULL if not found.
*/
mchunk_t    *find_mbin_best_fit_free_mchunk(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *selected_free_mchunk;
    mchunk_t    *(*find_mbin_fptr)(mchunk_t**, size_t);

    if (allocation_size <= MCHUNK_TINY_MAX_DATA_SIZE)
        find_mbin_fptr = find_mbin_mchunk_first_fit;
    else if (allocation_size <= MCHUNK_SMALL_MAX_DATA_SIZE)
        find_mbin_fptr = find_mbin_mchunk_good_enough_fit;
    else
        find_mbin_fptr = find_mbin_mchunk_best_fit;

    return find_mbin_fptr(mbin, allocation_size);
}
