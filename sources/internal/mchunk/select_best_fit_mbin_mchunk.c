/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_best_fit_mbin_mchunk.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 04:07:10 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 04:07:10 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static mchunk_t *fn_select_mbin_mchunk_first_fit(mchunk_t *mbin, size_t allocation_size)
{
    mchunk_t    *curr_mchunk;
    size_t      desired_mchunk_size;

    desired_mchunk_size = GET_MCHUNK_SIZE(allocation_size);

    curr_mchunk = mbin;
    while (curr_mchunk)
    {
        if (curr_mchunk->allocation_size == allocation_size)
            return curr_mchunk;
        if (curr_mchunk->allocation_size >= desired_mchunk_size)
            return curr_mchunk;

        curr_mchunk = curr_mchunk->next_free_mchunk;
    }

    return NULL;
}

static mchunk_t *fn_select_mbin_mchunk_best_fit(mchunk_t *mbin, size_t allocation_size)
{
    mchunk_t    *curr_mchunk;
    mchunk_t    *best_fit_mchunk;
    size_t      desired_mchunk_size;

    desired_mchunk_size = GET_MCHUNK_SIZE(allocation_size);
    best_fit_mchunk = NULL;

    curr_mchunk = mbin;
    while (curr_mchunk)
    {
        if (curr_mchunk->allocation_size == allocation_size)
            return curr_mchunk;
        if (curr_mchunk->allocation_size >= desired_mchunk_size)
        {
            if (!best_fit_mchunk || curr_mchunk->allocation_size <= best_fit_mchunk->allocation_size)
                best_fit_mchunk = curr_mchunk;
        }

        curr_mchunk = curr_mchunk->next_free_mchunk;
    }

    return best_fit_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *select_best_fit_mbin_mchunk(mchunk_t *mbin, size_t allocation_size)
{
    mchunk_t *(*strategy)(mchunk_t*, size_t);

    if (!mbin)
        return NULL;

    if (allocation_size <= TINY_MCHUNK_MAX_ALLOCATION_SIZE)
        strategy = fn_select_mbin_mchunk_first_fit;
    else if (allocation_size <= SMALL_MCHUNK_MAX_ALLOCATION_SIZE)
        strategy = fn_select_mbin_mchunk_best_fit;
    else
        strategy = fn_select_mbin_mchunk_best_fit;

    return strategy(mbin, allocation_size);
}
