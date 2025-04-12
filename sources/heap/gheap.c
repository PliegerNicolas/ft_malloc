/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_heap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 17:23:19 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-30 17:23:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* Global variable(s) */

/**
* @brief Global variable used throughout this dynamic library.
*
* @note As a global variable. On start-up it is initialized to 0.
* So by default `.is_initialized` is set to `false`.
*/
heap_t  gheap;

/**
 * @brief Initialize the global heap structure.
 * @note Should happen the first time malloc or similar is called.
*/
status_t    initialize_gheap(heap_t *gheap)
{
    status_t    status = SUCCESS;

    *gheap = new_heap(&status);
    if (status == FAILURE)
        clear_heap(gheap);

    return status;
}