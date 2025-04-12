/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 15:08:07 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 15:08:07 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    show_alloc_mem()
{
    if (!gheap.is_initialized)
        return;

    show_heap(&gheap, STDOUT_FILENO);
}
