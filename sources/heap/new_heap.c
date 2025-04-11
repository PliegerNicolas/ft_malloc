/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 14:51:49 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-10 14:51:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

heap_t  new_heap(status_t *status)
{
    heap_t  heap;

    heap.marena = new_marena(status);
    if (*status == FAILURE)
        return heap;

    heap.is_initialized = true;
    return heap;
}