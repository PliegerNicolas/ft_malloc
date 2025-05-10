/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:23 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:23 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *malloc(size_t size)
{
    mchunk_t    *allocated_mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return NULL;

    if ((allocated_mchunk = alloc_mchunk(size)) == STATUS_FAILURE)
        return NULL;

    return GET_MCHUNK_DATA_PTR(allocated_mchunk);
}
