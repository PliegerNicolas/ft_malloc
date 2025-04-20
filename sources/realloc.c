/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 15:02:37 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 15:02:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *realloc(void *ptr, size_t size)
{
    if (init_gmarena_once(&gmarena, NUM_INITIAL_BOUNDED_MREGIONS) == STATUS_FAILURE)
        return NULL;
    return NULL;
}
