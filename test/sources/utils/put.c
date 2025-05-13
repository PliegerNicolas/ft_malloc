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

void    put_title(const char *title, char *color, int fd)
{
    if (!title)
        return;

    if (color)
        ft_putstr_fd(color, fd);

    ft_putstr_fd(title, fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);
}

void    put_expected_result(const char *expected_result, int fd)
{
    if (!expected_result)
        return;

    ft_putstr_fd("🞄 Expected: ", fd);
    ft_putstr_fd(expected_result, fd);
    ft_putchar_fd('\n', fd);
}

void    put_test_result(void *ptr, const char *error, int fd)
{
    ft_putstr_fd("🞄 Got: ", fd);
    ft_putptr_fd(ptr, fd);
    if (error && *error)
    {
        ft_putchar_fd(' ', fd);
        ft_putstr_fd(error, fd);
    }
    ft_putchar_fd('\n', fd);
}

void    put_macro_result_size_t(size_t macro, int fd)
{
    ft_putstr_fd("🞄 Got: ", fd);
    ft_putsize_t_fd(macro, fd);
    ft_putchar_fd('\n', fd);
}

void    put_macro_result_int(int macro, int fd)
{
    ft_putstr_fd("🞄 Got: ", fd);
    ft_putint_fd(macro, fd);
    ft_putchar_fd('\n', fd);
}

void    put_ptr_comparison(void *ptr1, void*ptr2, int fd)
{
    ft_putstr_fd("🞄 Got: ", fd);
    ft_putptr_fd(ptr1, fd);
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(ptr2, fd);

    if (ptr1 && ptr2)
    {
        ft_putstr_fd(" (offset: ", fd);
        ft_putint_fd((unsigned char *)ptr2 - (unsigned char *)ptr1, fd);
        ft_putstr_fd(" bytes)", fd);
    }
    ft_putchar_fd('\n', fd);
}

void    put_test_result_ptr_comparison(void *ptr1, void *ptr2, const char *error, int fd)
{
    ft_putstr_fd("🞄 Got: ", fd);
    ft_putptr_fd(ptr1, fd);
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(ptr2, fd);

    if (ptr1 && ptr2)
    {
        ft_putstr_fd(" (offset: ", fd);
        ft_putint_fd((unsigned char *)ptr2 - (unsigned char *)ptr1, fd);
        ft_putendl_fd(" bytes)", fd);
    }

    if (error && *error)
    {
        ft_putchar_fd(' ', fd);
        ft_putstr_fd(error, fd);
    }
    ft_putchar_fd('\n', fd);
}

void    put_memory_state(const char *operation, int fd)
{
    ft_putstr_fd(BOLD_CYAN, fd);
    ft_putstr_fd("Memory state: ", fd);
    if (operation)
        ft_putstr_fd(operation, fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);
    please_show_alloc_mem();
}