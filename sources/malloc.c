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
    mchunk_t    *tmp;

    if (!gheap.is_initialized && initialize_gheap(&gheap) == FAILURE)
        return NULL; // Setup more error details. errno ?

    tmp = find_free_mchunk(&gheap, size);

    // Check quel bin.
    // Check si une place de libre dans le bien donné.
    // Remplir.
    // Si pas de place, nouveau mbin prepended.

    // clear_heap(&gheap);

    return NULL;
}
