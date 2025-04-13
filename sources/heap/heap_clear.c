/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:11 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:11 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Deallocates and resets internal state of the given `heap_t*`.
 * 
 * @note Does nothing if heap is NULL.
*/
void    heap_clear(heap_t *heap)
{
    if (!heap)
        return;

    marena_clear(&heap->marena);
    heap->is_initialized = false;
}
