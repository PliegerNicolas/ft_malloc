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
    if (color)
        ft_putstr_fd(color, fd);

    ft_putstr_fd(title, fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);
}

void    put_expected_result(const char *expected_result, int fd)
{
    ft_putstr_fd("🞄 Expected: ", fd);
    ft_putendl_fd(expected_result, fd);
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

void    put_memory_state(int fd)
{
    ft_putstr_fd(BOLD_CYAN, fd);
    ft_putstr_fd("Memory state: ", fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);
    please_show_alloc_mem();
}
