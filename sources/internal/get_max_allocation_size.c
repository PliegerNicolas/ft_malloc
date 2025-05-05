/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_allocation_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-05 12:03:16 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-05 12:03:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

size_t  get_max_allocation_size(size_t allocation_size)
{
    static size_t   max_allocation_size;

    if (allocation_size > max_allocation_size)
        max_allocation_size = allocation_size;

    return max_allocation_size;
}
