/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:24:52 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:24:52 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    show_alloc_mem()
{
    size_t  allocated_bytes;

    if (gmutex_lock() == STATUS_FAILURE)
        return;
    if (init_gmarena_once() == STATUS_FAILURE)
        return (void)gmutex_unlock();
    allocated_bytes = print_marena(&gmarena, STDOUT_FILENO, MALLOC_DEBUG);    
    gmutex_unlock();
}
