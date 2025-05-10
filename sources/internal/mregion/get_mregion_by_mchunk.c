/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mregion_by_mchunk.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 03:30:29 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 03:30:29 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   **get_mregion_by_mchunk(marena_t *marena, mchunk_t *mchunk, size_t allocation_size)
{
    mregion_t   **mregion_head;
    mregion_t   **current_mregion;

    if (!marena || !mchunk)
        return printerr("get_mregion_by_mchunk()", "Wrong parameters", NULL), STATUS_FAILURE;

    if ((mregion_head = map_allocation_size_to_marena_mregion_head(marena, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    current_mregion = mregion_head;
    while (*current_mregion)
    {
        if (does_mregion_contain_mchunk(*current_mregion, mchunk))
            return current_mregion;
        current_mregion = &(*current_mregion)->next;
    }

    return STATUS_FAILURE;
}
