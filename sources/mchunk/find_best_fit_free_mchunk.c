/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_fit_free_mchunk.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-22 21:16:58 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-22 21:16:58 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *find_best_fit_free_mchunk(mchunk_t **mbin, size_t allocation_size)
{
    mchunk_t    *current_free_mchunk;
    size_t      allocation_mchunk_size;

    if (!mbin)
        return STATUS_FAILURE;
    
    allocation_mchunk_size = map_allocation_size_to_mchunk_size(allocation_size);

    current_free_mchunk = *mbin;
    while (current_free_mchunk && current_free_mchunk->allocation_size < allocation_mchunk_size)
        current_free_mchunk = current_free_mchunk->next_free_mchunk;

    return current_free_mchunk;
}
