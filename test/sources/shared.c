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

void    put_colored(char *color, char *title, bool newline, int fd)
{
    ft_putstr_fd(color, fd);
    ft_putstr_fd(title, fd);
    ft_putstr_fd(RESET, fd);
    if (newline)
        ft_putchar_fd('\n', fd);
}

void    put_size_t(size_t n, const char *expected_value, int fd)
{
    ft_putsize_t_fd(n, fd);
    if (expected_value)
    {
        ft_putstr_fd(" (expected: ", fd);
        ft_putstr_fd(expected_value, fd);
        ft_putstr_fd(")", fd);
    }
    ft_putchar_fd('\n', fd);
}

void    put_ptr(void *ptr, const char *expected_value, int fd)
{
    ft_putptr_fd(ptr, fd);
    if (expected_value)
    {
        ft_putstr_fd(" (expected: ", fd);
        ft_putstr_fd(expected_value, fd);
        ft_putstr_fd(")", fd);
    }
    ft_putchar_fd('\n', fd);
}

void    put_relative_ptrs(void *ptr1, void *ptr2, const char *expected_value, int fd)
{
    ft_putptr_fd(ptr1, fd);
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(ptr2, fd);
    if (expected_value)
    {
        ft_putstr_fd(" (expected: ", fd);
        ft_putstr_fd(expected_value, fd);
        ft_putstr_fd(")", fd);
    }
    ft_putchar_fd('\n', fd);
}
