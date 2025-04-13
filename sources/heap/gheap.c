/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gheap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:07 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* Global variable(s) */

/**
 * @brief Global variable representing this thread's `heap_t`.
 * 
 * @note As a global variable, on start-up, it is initialize to 0.
 * By default `.is_initialized` is thus set to `false`.
*/
heap_t  gheap;

/**
 * @brief Initialize a given `heap_t*`.
 * @note State of `heap_t` is defined by `.is_initialized`.
 * 
 * @return A status_t. Set to `SUCCESSFUL` if the operation succeeded, else `FAILURE`.
*/
status_t    gheap_initialize(heap_t *gheap)
{
    status_t    status = SUCCESS;

    *gheap = heap_create(&status);
    if (status == FAILURE)
        heap_clear(gheap);

    return status;
}
