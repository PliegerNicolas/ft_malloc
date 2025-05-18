/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mbin_if_necessary.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-18 11:53:36 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-18 11:53:36 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    update_mbin_if_necessary(mregion_t *mregion, mchunk_t *free_mchunk)
{
    if (!mregion || !free_mchunk)
        return;

    if (!mregion->mbin || mregion->mbin->state != FREE)
        mregion->mbin = free_mchunk;

    while (mregion->mbin->prev_free_mchunk)
        mregion->mbin = mregion->mbin->prev_free_mchunk;
}
