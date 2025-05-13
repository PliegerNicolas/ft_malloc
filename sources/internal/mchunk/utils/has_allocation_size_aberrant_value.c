/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_allocation_size_aberrant_value.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-16 17:16:31 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-16 17:16:31 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    has_allocation_size_aberrant_value(size_t allocation_size)
{
    if (allocation_size > MAX_ALLOCATION_SIZE)
        return printerr("has_allocation_size_aberrant_value()", "max allocation size exceeded", NULL), true;
    return false;
}
