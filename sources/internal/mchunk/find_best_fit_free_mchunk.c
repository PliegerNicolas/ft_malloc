/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_fit_free_mchunk.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 20:41:33 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-04 20:41:33 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static mchunk_t **find_mbin_mchunk_first_fit(mregion_t **mregion, size_t allocation_size)
{
    mchunk_t    **curr_mchunk;
    size_t      alloc_size;
    size_t      desired_free_mchunk_size;

    if (!mregion || !*mregion)
        return NULL;

    desired_free_mchunk_size = GET_MCHUNK_SIZE(allocation_size);

    curr_mchunk = &(*mregion)->mbin;
    while (*curr_mchunk)
    {
        alloc_size = (*curr_mchunk)->allocation_size;

        if (alloc_size == allocation_size)
            return curr_mchunk;

        if (alloc_size >= desired_free_mchunk_size)
            return curr_mchunk;

        curr_mchunk = &(*curr_mchunk)->next_free_mchunk;
    }

    return NULL;
}

static mchunk_t **find_mbin_mchunk_first_good_enough_fit(mregion_t **mregion, size_t allocation_size)
{
    mchunk_t    **curr_mchunk;
    size_t      alloc_size;
    size_t      desired_free_mchunk_size;
    size_t      good_enough_size_threshold;

    if (!mregion || !*mregion)
        return NULL;

    desired_free_mchunk_size = GET_MCHUNK_SIZE(allocation_size);
    good_enough_size_threshold = desired_free_mchunk_size * 1.15;

    curr_mchunk = &(*mregion)->mbin;
    while (*curr_mchunk)
    {
        alloc_size = (*curr_mchunk)->allocation_size;

        if (alloc_size == allocation_size)
            return curr_mchunk;

        if (alloc_size >= desired_free_mchunk_size &&
            alloc_size <= good_enough_size_threshold)
            return curr_mchunk;

        curr_mchunk = &(*curr_mchunk)->next_free_mchunk;
    }

    return NULL;
}

static mchunk_t **find_mbin_mchunk_best_fit(mregion_t **mregion, size_t allocation_size)
{
    mchunk_t    **curr_mchunk;
    size_t      alloc_size;
    size_t      desired_free_mchunk_size;
    mchunk_t    **best_fit_mchunk;

    if (!mregion || !*mregion)
        return NULL;

    desired_free_mchunk_size = GET_MCHUNK_SIZE(allocation_size);
    
    best_fit_mchunk = NULL;
    curr_mchunk = &(*mregion)->mbin;
    while (*curr_mchunk)
    {
        alloc_size = (*curr_mchunk)->allocation_size;

        if (alloc_size == allocation_size)
            return curr_mchunk;
        
        if (alloc_size >= desired_free_mchunk_size &&
            (!best_fit_mchunk || alloc_size <= (*best_fit_mchunk)->allocation_size))
                best_fit_mchunk = curr_mchunk;

        curr_mchunk = &(*curr_mchunk)->next_free_mchunk;
    }

    return best_fit_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    **find_best_fit_free_mchunk(mregion_t **mregion, size_t allocation_size)
{
    find_mregion_best_mchunk_fn_t   fn;

    if (!mregion || !*mregion)
        return NULL;

    if (allocation_size <= TINY_MCHUNK_MAX_ALLOCATION_SIZE)
        fn = find_mbin_mchunk_first_fit;
    else if (allocation_size <= SMALL_MCHUNK_MAX_ALLOCATION_SIZE)
        fn = find_mbin_mchunk_first_good_enough_fit;
    else
        fn = find_mbin_mchunk_best_fit;

    return fn(mregion, allocation_size);
}
