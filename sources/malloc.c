/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:23 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:23 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *malloc(size_t size)
{
    mregion_t   **mregion;
    mchunk_t    **free_mchunk;
    mchunk_t    *used_mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    if ((free_mchunk = get_or_create_best_fit_free_mchunk(&gmarena, size)) == STATUS_FAILURE)
        return NULL;

    if ((used_mchunk = use_mchunk(free_mchunk, size)) == STATUS_FAILURE)
        return NULL;

    if ((mregion = mchunk_find_corresponding_mregion(&gmarena, used_mchunk)) == STATUS_FAILURE)
        return NULL;
    (*mregion)->used_mchunks += 1;

    return GET_MCHUNK_DATA_PTR(used_mchunk);
}
