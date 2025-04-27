/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 21:37:21 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-04 21:37:21 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static mchunk_t *use_mchunk_on_exact_match(mchunk_t **free_mchunk, size_t allocation_size)
{
    mchunk_t    *prev_free_mchunk;
    mchunk_t    *next_free_mchunk;

    if (!free_mchunk || !*free_mchunk)
        return STATUS_FAILURE;

    prev_free_mchunk = (*free_mchunk)->prev_free_mchunk;
    next_free_mchunk = (*free_mchunk)->next_free_mchunk;

    (*free_mchunk)->prev_free_mchunk = NULL;
    (*free_mchunk)->next_free_mchunk = NULL;

    prev_free_mchunk->next_free_mchunk = (*free_mchunk);
    next_free_mchunk->prev_free_mchunk = (*free_mchunk);

    return *free_mchunk;
}

static mchunk_t *use_mchunk_through_partitioning(mchunk_t **free_mchunk, size_t allocation_size)
{
    size_t      used_mchunk_size;
    mchunk_t    *used_mchunk, *remainder_mchunk;
    mchunk_t    original_mchunk_data;

    if (!free_mchunk || !*free_mchunk)
        return STATUS_FAILURE;

    used_mchunk_size = GET_MCHUNK_SIZE(allocation_size);

    if (used_mchunk_size > (*free_mchunk)->allocation_size)
        return STATUS_FAILURE;

    original_mchunk_data = **free_mchunk;

    used_mchunk = *free_mchunk;
    *used_mchunk = (mchunk_t) {
        .state = USED,
        .allocation_size = allocation_size,
        .prev_allocation_size = original_mchunk_data.prev_allocation_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    remainder_mchunk = GET_NEXT_MCHUNK(used_mchunk);
    *remainder_mchunk = (mchunk_t) {
        .state = FREE,
        .allocation_size = original_mchunk_data.allocation_size - used_mchunk_size,
        .prev_allocation_size = allocation_size,
        .next_free_mchunk = original_mchunk_data.next_free_mchunk,
        .prev_free_mchunk = original_mchunk_data.prev_free_mchunk,
    };

    *free_mchunk = remainder_mchunk;
    return used_mchunk;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

mchunk_t    *use_mchunk(mchunk_t **free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;

    if (!free_mchunk || !*free_mchunk || (*free_mchunk)->state == USED)
        return STATUS_FAILURE;

    if ((*free_mchunk)->allocation_size == allocation_size)
        used_mchunk = use_mchunk_on_exact_match(free_mchunk, allocation_size);
    else
        used_mchunk = use_mchunk_through_partitioning(free_mchunk, allocation_size);

    if (used_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;

    return used_mchunk;
}
