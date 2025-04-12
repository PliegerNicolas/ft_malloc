/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunkify_mbin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 13:01:59 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 13:01:59 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief
*/
void    mchunkify_mbin(mchunk_t **initial_mchunk, size_t target_mchunk_size)
{
    mchunk_t    *current_mchunk;
    mchunk_t    *next_mchunk;

    if (!initial_mchunk || !*initial_mchunk)
        return;

    current_mchunk = *initial_mchunk;
    while (current_mchunk->size > target_mchunk_size)
    {
        next_mchunk = (mchunk_t *)((unsigned char *)current_mchunk + target_mchunk_size);
        *next_mchunk = (mchunk_t) {
            .state = FREE,
            .size = current_mchunk->size - target_mchunk_size,
            .prev_size = target_mchunk_size,
            .requested_size = 0,
            .next_free_mchunk = NULL,
            .prev_free_mchunk = current_mchunk,
        };

        current_mchunk->size = target_mchunk_size;
        current_mchunk->next_free_mchunk = next_mchunk;

        current_mchunk = next_mchunk;
    };
}