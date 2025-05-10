/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mchunk_in_mregion_boundary.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 23:55:49 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 23:55:49 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    is_mchunk_in_mregion_boundary(mregion_t *mregion, mchunk_t *mchunk)
{
    unsigned char   *mregion_left_data_boundary;
    unsigned char   *mregion_right_data_boundary;

    if (!mregion || !mchunk)
        return false;

    mregion_left_data_boundary = (unsigned char *)mregion + MREGION_HEADER_SIZE;
    mregion_right_data_boundary = (unsigned char *)mregion + mregion->size;

    return (unsigned char *)mchunk >= mregion_left_data_boundary && (unsigned char *)mchunk < mregion_right_data_boundary;
}
