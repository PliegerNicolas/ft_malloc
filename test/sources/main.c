/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:35 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:35 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void print_options(const char *options[4], size_t n, int fd)
{
    ft_putstr_fd("🞄 Options: ", fd);

    for (size_t i = 0; i < n; i++)
    {
        ft_putstr_fd(options[i], fd);
        if (i != (n - 1))
            ft_putstr_fd(", ", fd);
    }

    ft_putchar_fd('\n', fd);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

int main(int argc, char **argv)
{
    static const char   *options[4] = { "MACROS", "MALLOC", "REALLOC", "FREE" };
    const int           fd = STDOUT_FILENO;

    if (argc < 2 || !argv[1])
        return ft_putendl_fd("Error: one parameter expected.", STDERR_FILENO), print_options(options, 5, STDERR_FILENO), 1;

    if (ft_strncmp(ft_toupper_str(argv[1]), options[0], ft_strlen(options[0]) + 1) == 0)
        test_macros(fd);
    else if (ft_strncmp(ft_toupper_str(argv[1]), options[1], ft_strlen(options[1]) + 1) == 0)
        test_malloc(fd);
    else if (ft_strncmp(ft_toupper_str(argv[1]), options[2], ft_strlen(options[2]) + 1) == 0)
        test_realloc(fd);
    else if (ft_strncmp(ft_toupper_str(argv[1]), options[3], ft_strlen(options[3]) + 1) == 0)
        test_free(fd);
    else
        return ft_putendl_fd("Error: unrecognized parameter.", STDERR_FILENO), print_options(options, 4, STDERR_FILENO), 1;

    return 0;
}
