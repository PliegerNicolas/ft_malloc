/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:39 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:39 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    put_title(char *color, char *title, int fd)
{
    ft_putstr_fd(color, fd);
    ft_putstr_fd(title, fd);
    ft_putendl_fd(RESET, fd);
}

void    put_size_t_macro(char *title, size_t value, char *details, int fd)
{
    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putsize_t_fd(value, fd);
    if (ft_strlen(details) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(details, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}

void    put_ptr_macro(char *title, void *ptr, char *details, int fd)
{
    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putptr_fd(ptr, fd);
    if (ft_strlen(details) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(details, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}

void    put_macro_with_relative_ptr_addresses(char *title, void *src_ptr, void *dest_ptr, char *details, int fd)
{
    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putptr_fd(src_ptr, fd);
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(dest_ptr, fd);
    if (ft_strlen(details) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(details, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}