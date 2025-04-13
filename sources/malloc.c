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

// Gérer getrlimit.

void    *malloc(size_t size)
{
    if (!gheap.is_initialized && gheap_initialize(&gheap) == FAILURE)
        return NULL; // Setup more error details. errno ?

    if (allocate_mchunk(&gheap, size) == FAILURE)
        return NULL;

    // Check quel bin.
    // Check si une place de libre dans le bien donné.
    // Remplir.
    // Si pas de place, nouveau mbin prepended.

    // clear_heap(&gheap);

    return NULL;
}
