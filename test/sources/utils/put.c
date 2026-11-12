/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:28:39 by nplieger          #+#    #+#             */
/*   Updated: 2026/11/12 21:16:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

// Tests run in threads through run_in_thread(), which can't return a result.
// Counting checks here avoids threading a counter through every test signature.
// The counter is static and local to this function: no other file can reach it.
typedef struct checks_count
{
    size_t  total;
    size_t  failed;
} checks_count_t;

static checks_count_t   *get_checks_count(void)
{
    static checks_count_t   checks_count;

    return &checks_count;
}

bool    put_check(bool ok, int fd)
{
    checks_count_t  *checks_count = get_checks_count();

    checks_count->total++;
    if (!ok)
        checks_count->failed++;
    ft_putendl_fd(ok ? BOLD_GREEN "🞄 ✔ PASS" RESET : BOLD_RED "🞄 ✘ FAIL" RESET, fd);
    return ok;
}

int     put_checks_summary(int fd)
{
    checks_count_t  *checks_count = get_checks_count();

    ft_putstr_fd(checks_count->failed ? BOLD_RED : BOLD_GREEN, fd);
    ft_putsize_t_fd(checks_count->total, fd);
    ft_putstr_fd(" checks, ", fd);
    ft_putsize_t_fd(checks_count->failed, fd);
    ft_putstr_fd(" failed", fd);
    ft_putendl_fd(RESET, fd);
    return checks_count->failed != 0;
}

static bool is_hex_digit(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

bool    matches_expected(const char *expected, const char *got)
{
    while (*expected)
    {
        if (ft_strncmp(expected, "0x...", 5) == 0)
        {
            if (ft_strncmp(got, "0x", 2) != 0 || !is_hex_digit(got[2]))
                return false;
            expected += 5;
            got += 2;
            while (is_hex_digit(*got))
                got++;
        }
        else if (*expected++ != *got++)
            return false;
    }
    return *got == '\0';
}

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
