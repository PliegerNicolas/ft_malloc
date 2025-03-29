/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 15:44:16 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 15:44:16 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

static void test_size_t_macro(char *name, size_t value, int fd)
{
    ft_putstr_fd("- ", fd);
    ft_putstr_fd(name, fd);
    ft_putstr_fd(": ", fd);

    ft_putsize_t_fd(value, fd);

    ft_putchar_fd('\n', fd);
}

static void test_get_mchunk_data_size(size_t size, char *details)
{
    mchunk_t    mchunk = {
        .state = FREE,
        .size = size,
        .prev_size = 0,
        .next_free_chunk = NULL,
        .prev_free_chunk = NULL,
    };

    ft_putstr_fd("- GET_MCHUNK_DATA_SIZE(ptr) -> ", 1);
    ft_putstr_fd(details, 1);
    ft_putstr_fd(": ", 1);
    ft_putsize_t_fd(GET_MCHUNK_DATA_SIZE(&mchunk), 1);
    ft_putchar_fd('\n', 1);
}

static void test_get_mchunk_data_ptr()
{
    mchunk_t    mchunk = {
        .state = FREE,
        .size = 0,
        .prev_size = 0,
        .next_free_chunk = NULL,
        .prev_free_chunk = NULL,
    };

    char  *ptr = GET_MCHUNK_DATA_PTR(&mchunk);

    ft_putstr_fd("- GET_MCHUNK_DATA_PTR(ptr): ", 1);
    ft_putendl_fd("TODO !!!!!!!!!!!!!!!!!!!!!", 1); // Need to print address here.
}

/* *********************** */

static void test_global_macros()
{
    write_title("Testing global macros:", 1);

    test_size_t_macro("PAGE_SIZE", PAGE_SIZE, 1);
    test_size_t_macro("MMAP_PROTECTIONS", MMAP_PROTECTIONS, 1);
    test_size_t_macro("MMAP_FLAGS", MMAP_FLAGS, 1);
}

static void test_mchunk_macros()
{
    write_title("Testing mchunk macros:", 1);

    test_size_t_macro("TARGET_TINY_CHUNK_SIZE", TARGET_TINY_CHUNK_SIZE, 1);
    test_size_t_macro("TARGET_SMALL_CHUNK_SIZE", TARGET_SMALL_CHUNK_SIZE, 1);

    test_size_t_macro("TARGET_MIN_ALLOCATIONS_PER_MBIN", TARGET_MIN_ALLOCATIONS_PER_MBIN, 1);
    test_size_t_macro("TARGET_MIN_ALLOCATIONS_PER_LARGE_MBIN", TARGET_MIN_ALLOCATIONS_PER_LARGE_MBIN, 1);

    test_size_t_macro("TARGET_INITIAL_TINY_MBINS", TARGET_INITIAL_TINY_MBINS, 1);
    test_size_t_macro("TARGET_INITAL_SMALL_MBINS", TARGET_INITAL_SMALL_MBINS, 1);

    test_size_t_macro("MCHUNK_ALIGNED_SIZE", MCHUNK_ALIGNED_SIZE, 1);

    test_size_t_macro("TINY_MCHUNK_SIZE", TINY_MCHUNK_SIZE, 1);
    test_size_t_macro("SMALL_MCHUNK_SIZE", SMALL_MCHUNK_SIZE, 1);

    test_size_t_macro("MAX_TINY_MCHUNK_DATA_SIZE", MAX_TINY_MCHUNK_DATA_SIZE, 1);
    test_size_t_macro("MAX_SMALL_MCHUNK_DATA_SIZE", MAX_SMALL_MCHUNK_DATA_SIZE, 1);

    test_size_t_macro("TINY_MBIN_SIZE", TINY_MBIN_SIZE, 1);
    test_size_t_macro("SMALL_MBIN_SIZE", SMALL_MBIN_SIZE, 1);

    test_get_mchunk_data_size(0, "With mchunk_ptr->size == 0");
    test_get_mchunk_data_size(100, "With mchunk_ptr->size == 100");
    
    test_get_mchunk_data_ptr();
}

void    test_macros()
{
    test_global_macros();
    test_mchunk_macros();
}
