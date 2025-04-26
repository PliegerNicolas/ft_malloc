/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 22:12:26 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 22:12:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    use_mchunk(mchunk_t *free_mchunk, size_t allocation_size)
{
    mchunk_t    *used_mchunk;

    *used_mchunk = (mchunk_t) {
        .allocation_size = 0,
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    *free_mchunk = (mchunk_t) {
        .allocation_size = 0,
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };
}