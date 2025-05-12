/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_free_mchunk_in_mbin.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 13:16:25 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 13:16:25 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

status_t    insert_free_mchunk_in_mregion_mbin(mregion_t *mregion, mchunk_t *free_mchunk)
{
    mchunk_t    **insertion_pos;

    if (!mregion || !free_mchunk)
        return printerr("insert_free_mchunk_in_mregion_mbin()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (!does_mregion_contain_mchunk(mregion, free_mchunk) || free_mchunk->state != FREE)
        return printerr("insert_free_mchunk_in_mregion_mbin()", "Wrong parameters", NULL), STATUS_FAILURE;

    insertion_pos = &mregion->mbin;
    while (*insertion_pos && *insertion_pos < free_mchunk)
        insertion_pos = &(*insertion_pos)->next_free_mchunk;

    if (*insertion_pos)
    {
        free_mchunk->prev_free_mchunk = (*insertion_pos)->prev_free_mchunk;
        (*insertion_pos)->prev_free_mchunk = free_mchunk;
    }
    free_mchunk->next_free_mchunk = *insertion_pos;

    return (*insertion_pos = free_mchunk), STATUS_SUCCESS;
}
