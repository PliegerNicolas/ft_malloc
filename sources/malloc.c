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
    mchunk_t    *free_mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    free_mchunk = find_marena_best_fit_free_mchunk(&gmarena, size);
    if (free_mchunk == STATUS_FAILURE)
        return NULL;

    return NULL;
}
