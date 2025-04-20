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

void    *malloc(size_t size)
{
    mregion_t   *mregion;

    if (init_gmarena_once(&gmarena, NUM_INITIAL_BOUNDED_MREGIONS) == STATUS_FAILURE)
        return NULL;

    mregion = pick_or_create_mregion(&gmarena, size);
    if (mregion == STATUS_FAILURE)
        return NULL;
    
    return NULL;
}
