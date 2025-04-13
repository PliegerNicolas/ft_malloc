/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:15 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:15 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Create and initializes to default values a new `heap_t`.
 * 
 * @return A `heap_t`.
 * The value of the parameter `status` is set to `SUCCESS` if initialization succeeded,
 * or `FAILURE` if it failed.
*/
heap_t  heap_create(status_t *status)
{
    heap_t  heap;

    heap.marena = marena_create(status);
    if (*status == FAILURE)
        return heap;

    heap.is_initialized = true;
    return heap;
}
