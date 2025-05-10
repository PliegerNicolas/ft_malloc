/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mchunk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 16:22:20 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 16:22:20 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *alloc_mchunk(size_t size)
{
    mregion_t   **mregion;
    mchunk_t    **free_mchunk;
    mchunk_t    *used_mchunk;

    if ((free_mchunk = get_or_create_marena_best_fit_free_mchunk(&gmarena, size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    coalesce_with_next_free_mchunks(*free_mchunk, (*free_mchunk)->next_free_mchunk);
    coalesce_with_prev_free_mchunks(free_mchunk, (*free_mchunk)->prev_free_mchunk);

    if ((used_mchunk = use_mchunk(free_mchunk, size)) == STATUS_FAILURE)
        return STATUS_FAILURE;
    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, used_mchunk)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    (*mregion)->used_mchunks += 1;

    return used_mchunk;
}
