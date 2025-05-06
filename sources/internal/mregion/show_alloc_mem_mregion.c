/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_mregion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:32:45 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:32:45 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void put_mregion_title(mregion_t *mregion, const char *mregion_name, int fd)
{
    ft_putstr_fd((char *)mregion_name, fd);
    ft_putstr_fd(" : ", fd);
    ft_putptr_fd(mregion, fd);
    ft_putchar_fd('\n', fd);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

size_t  show_alloc_mem_mregion(mregion_t *mregion, const char *mregion_name)
{
    mregion_t   *current_mregion;
    size_t      total_allocated_bytes;
    
    if (!mregion)
        return 0;
    
    current_mregion = mregion;
    total_allocated_bytes = 0;
    while (current_mregion)
    {
        put_mregion_title(current_mregion, mregion_name, STDOUT_FILENO);
        total_allocated_bytes += show_alloc_mem_mchunks(current_mregion);
        current_mregion = current_mregion->next;
    }
    
    return total_allocated_bytes;
}
