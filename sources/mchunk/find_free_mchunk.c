/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_free_mchunk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 21:18:50 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 21:18:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    *find_free_mchunk(heap_t *heap, size_t requested_data_size)
{
    size_t  target_mbin_size;
    
    target_mbin_size = get_mbin_size(requested_data_size);
    
    return NULL;
};