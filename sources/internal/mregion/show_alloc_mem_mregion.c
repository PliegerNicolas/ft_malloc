/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_mregion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:32:45 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:32:45 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  show_alloc_mem_mregion(mregion_t *mregion)
{
    mregion_t   *current_mregion;
    size_t      total_allocated_bytes;

    if (!mregion)
        return 0;

    current_mregion = mregion;
    total_allocated_bytes = 0;
    while (current_mregion)
    {
        total_allocated_bytes += show_alloc_mem_mchunks(current_mregion);
        current_mregion = current_mregion->next;
    }
    
    return total_allocated_bytes;
}
