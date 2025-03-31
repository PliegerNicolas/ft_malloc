/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uniform_mchunk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-31 04:02:30 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-31 04:02:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void set_uniform_mbin_initial_mchunk(mbin_t *mbin, size_t size)
{
    uniform_mchunk_t    *initial_mchunk;

    initial_mchunk = GET_MBIN_INITIAL_MCHUNK_PTR(mbin);

    *initial_mchunk = (uniform_mchunk_t) {
        .state = FREE,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    *mbin = (typeof(*mbin)) {
        .uniform_start = initial_mchunk,
        .size = size,
        .next = NULL,
        .prev = NULL,
    };
}