/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 03:13:12 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 03:13:12 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    printerr(const char *caller, const char *err, void *ptr)
{
    int fd;

    if (!err)
        return;

    gmutex_lock();

    fd = STDERR_FILENO;
    ft_putstr_fd("** ", fd);

    if (caller)
    {
        ft_putstr_fd(caller, fd);
        ft_putstr_fd(": ", fd);
    }

    ft_putstr_fd(err, fd);

    if (ptr)
    {
        ft_putstr_fd(": ", fd);
        ft_putptr_fd(ptr, fd);
    }

    ft_putendl_fd(" **", fd);

    gmutex_unlock();
}