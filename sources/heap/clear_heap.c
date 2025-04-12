/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_heap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 19:40:00 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 19:40:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Clear an existing `heap_t`.
 * @note Deallocate its content and resets its internal state.
*/
void    clear_heap(heap_t *heap)
{
    clear_marena(&heap->marena);
    heap->is_initialized = false;
}