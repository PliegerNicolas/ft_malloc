/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_find_corresponding_mregion.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 21:31:25 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-05 21:31:25 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   **mchunk_find_corresponding_mregion(marena_t *marena, mchunk_t *mchunk)
{
    mregion_t       **mregion_head;
    mregion_t       **current_mregion;
    unsigned char   *mregion_left_data_boundary;
    unsigned char   *mregion_right_data_boundary;

    if (!mchunk)
        return STATUS_FAILURE;

    mregion_head = map_allocation_size_to_marena_mregion_head(marena, mchunk->allocation_size);
    if (!mregion_head || !*mregion_head)
        return STATUS_FAILURE;

    current_mregion = mregion_head;
    while (*current_mregion)
    {
        mregion_left_data_boundary = (unsigned char *)(*current_mregion) + MREGION_HEADER_SIZE;
        mregion_right_data_boundary = (unsigned char *)(*current_mregion) + (*current_mregion)->size;

        if ((unsigned char *)mchunk >= mregion_left_data_boundary &&
            (unsigned char*)mchunk < mregion_right_data_boundary)
            return current_mregion;

        current_mregion = &(*current_mregion)->next;
    }

    return STATUS_FAILURE;
}
