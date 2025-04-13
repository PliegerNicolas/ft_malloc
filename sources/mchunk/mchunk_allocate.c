/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk_allocate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:09:38 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:09:38 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *allocate_mchunk(heap_t *heap, size_t requested_bytes)
{
    return NULL;
}
// {
//     mbin_t              **mbin;
//     mbin_category_t     mbin_category;
//     mbin_subcategory_t  mbin_subcategory;

//     if (!heap)
//         return FAILURE;

//     mbin = resolve_heap_mbin(heap, requested_bytes);
//     if (mbin == FAILURE)
//         return FAILURE;


//     // Find next free mchunk.
//     // SET.

//     return NULL;
// }