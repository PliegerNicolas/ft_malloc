/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 15:02:35 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 15:02:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// Check is initialisé.
// - Si non, setup les mmap pour chacun des bails.

void    *malloc(size_t size)
{
    if (!gheap.is_initialized)
        if (initialize_gheap(&gheap) == FAILURE)
            return NULL;

    clear_heap(&gheap);

    return NULL;
}
