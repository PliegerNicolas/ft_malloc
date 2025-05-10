/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_free_mchunk_in_mregion_mbin.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-10 17:14:13 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-10 17:14:13 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    insert_free_mchunk_in_mregion_mbin(mregion_t *mregion, mchunk_t *mchunk)
{
    mchunk_t    **insertion_pos;

    if (!mregion || !mchunk)
        return;

    if (mchunk->state != FREE)
        return;

    insertion_pos = &mregion->mbin;
    while (*insertion_pos && *insertion_pos < mchunk)
        insertion_pos = &(*insertion_pos)->next_free_mchunk;

    mchunk->prev_free_mchunk = (*insertion_pos)->prev_free_mchunk;
    if (*insertion_pos)
        (*insertion_pos)->prev_free_mchunk = mchunk;
    mchunk->next_free_mchunk = *insertion_pos;

    *insertion_pos = mchunk;
}
