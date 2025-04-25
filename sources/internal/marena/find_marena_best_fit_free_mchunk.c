/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_marena_best_fit_free_mchunk.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 22:00:15 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 22:00:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *find_marena_best_fit_free_mchunk(marena_t *marena, size_t allocation_size)
{
    mregion_t   *mregion_head;
    mchunk_t    *free_mchunk;

    if (!marena)
        return STATUS_FAILURE;

    mregion_head = find_marena_best_fit_mregion_head(marena, allocation_size);
    if (!mregion_head)
        return STATUS_FAILURE;

    free_mchunk = find_mregion_best_fit_free_mchunk(&mregion_head, allocation_size);
    if (free_mchunk == STATUS_FAILURE)
        return STATUS_FAILURE;
    return free_mchunk;
}