/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 21:19:27 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 21:19:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    put_title(char *color, char *title, int fd)
{
    ft_putstr_fd(color, fd);
    ft_putstr_fd(title, fd);
    ft_putendl_fd(RESET, fd);
}

void    put_size_t_macro(char *title, size_t value, char *expectation, int fd)
{
    const char*     base = "0123456789";
    const size_t    base_len = 10;

    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putsize_t_base_fd(value, base, base_len, fd);
    if (ft_strlen(expectation) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(expectation, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}

void    put_ptr_macro(char *title, void *ptr, char *expectation, int fd)
{
    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putptr_fd(ptr, fd);
    if (ft_strlen(expectation) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(expectation, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}

void    put_macro_with_relative_ptr_addresses(char *title, void *src_ptr, void *dest_ptr, char *expectation, int fd)
{
    ft_putstr_fd(title, fd);
    ft_putstr_fd(": ", fd);
    ft_putptr_fd(src_ptr, fd);
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(dest_ptr, fd);
    if (ft_strlen(expectation) > 0)
    {
        ft_putchar_fd(' ', fd);
        ft_putchar_fd('(', fd);
        ft_putstr_fd(expectation, fd);
        ft_putchar_fd(')', fd);
    };
    ft_putchar_fd('\n', fd);
}