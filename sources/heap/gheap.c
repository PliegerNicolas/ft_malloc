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

/*
* @brief Global variable used throughout this dynamic library.
*
* @note As a global variable. On start-up it is initialized to 0.
* This sets .is_initialized to false.
*/
heap_t  gheap;
