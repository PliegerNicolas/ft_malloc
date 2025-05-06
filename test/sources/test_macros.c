/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:46 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:46 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

static void test_macros_system()
{
    put_colored(CYAN, "॰ system macros", STDOUT_FILENO);

    put_size_t_macro("DESIRED_ALIGNMENT_BOUNDARY", DESIRED_ALIGNMENT_BOUNDARY, "expect => 16", STDOUT_FILENO);
    put_size_t_macro("ALIGNMENT_BOUNDARY", ALIGNMENT_BOUNDARY, "expect => 16", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("PAGE_SIZE", PAGE_SIZE, "expect => 4096", STDOUT_FILENO);
    
    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(0, 16)", ALIGN_UP(0, 16), "expect => 0", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(15, 16)", ALIGN_UP(15, 16), "expect => 16", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(16, 16)", ALIGN_UP(16, 16), "expect => 16", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(17, 16)", ALIGN_UP(17, 16), "expect => 32", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("CLAMP_MIN(60, 100)", CLAMP_MIN(60, 100), "expect => 100", STDOUT_FILENO);
    put_size_t_macro("CLAMP_MIN(120, 100)", CLAMP_MIN(120, 100), "expect => 120", STDOUT_FILENO);
    put_size_t_macro("CLAMP_MAX(120, 100)", CLAMP_MAX(120, 100), "expect => 100", STDOUT_FILENO);
    put_size_t_macro("CLAMP_MAX(60, 100)", CLAMP_MAX(60, 100), "expect => 60", STDOUT_FILENO);
}

static void test_macros_mregion()
{
    put_colored(CYAN, "॰ mregion macros", STDOUT_FILENO);

    put_size_t_macro("DESIRED_MCHUNKS_PER_BOUND_MREGION", DESIRED_MCHUNKS_PER_BOUND_MREGION, "expect => 124", STDOUT_FILENO);
    put_size_t_macro("DESIRED_MCHUNKS_PER_UNBOUND_MREGION", DESIRED_MCHUNKS_PER_UNBOUND_MREGION, "expect => 1", STDOUT_FILENO);
    put_size_t_macro("MCHUNKS_PER_BOUND_MREGION", MCHUNKS_PER_BOUND_MREGION, "expect => 124", STDOUT_FILENO);
    put_size_t_macro("MCHUNKS_PER_UNBOUND_MREGION", MCHUNKS_PER_UNBOUND_MREGION, "expect => 1", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE", DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, "expect => 3", STDOUT_FILENO);
    put_size_t_macro("INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE", INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, "expect => 3", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("MREGION_HEADER_SIZE", MREGION_HEADER_SIZE, "expect => 32", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("TINY_MREGION_SIZE", TINY_MREGION_SIZE, "expect => 8192", STDOUT_FILENO);
    put_size_t_macro("SMALL_MREGION_SIZE", SMALL_MREGION_SIZE, "expect => 65536", STDOUT_FILENO);
    put_size_t_macro("LARGE_MREGION_SIZE(20000)", LARGE_MREGION_SIZE(20000), "expect => 20480", STDOUT_FILENO);

    mregion_t mregion = {
        .mbin = NULL,
        .next = NULL,
        .size = TINY_MREGION_SIZE,
    };

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_macro_with_relative_ptr_addresses("GET_MREGION_FIRST_MCHUNK(mregion_ptr)", &mregion, GET_MREGION_FIRST_MCHUNK(&mregion), "expect => +0x20 offset (32 bytes)", STDOUT_FILENO);
}

static void test_macros_mchunk()
{
    put_colored(CYAN, "॰ mchunk macros", STDOUT_FILENO);

    put_size_t_macro("MCHUNK_HEADER_SIZE", MCHUNK_HEADER_SIZE, "expect => 48", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("GET_MCHUNK_SIZE(64)", GET_MCHUNK_SIZE(64), "expect => 112", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE", DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE, "expect => 64", STDOUT_FILENO);
    put_size_t_macro("DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE", DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "expect => 512", STDOUT_FILENO);
    put_size_t_macro("TINY_MCHUNK_MAX_ALLOCATION_SIZE", TINY_MCHUNK_MAX_ALLOCATION_SIZE, "expect => 64", STDOUT_FILENO);
    put_size_t_macro("SMALL_MCHUNK_MAX_ALLOCATION_SIZE", SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "expect => 512", STDOUT_FILENO);
    
    mchunk_t mchunk = {
        .allocation_size = 42,
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    void    *mchunk_data_ptr = GET_MCHUNK_DATA_PTR(&mchunk);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_macro_with_relative_ptr_addresses("GET_MCHUNK_DATA_PTR(mchunk_ptr)", &mchunk, mchunk_data_ptr, "expect => +0x30 offset (48 bytes)", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_macro_with_relative_ptr_addresses("GET_NEXT_MCHUNK(mchunk_ptr)", &mchunk, GET_NEXT_MCHUNK(&mchunk), "expect => +0x60 offset (96 bytes)", STDOUT_FILENO);
    put_macro_with_relative_ptr_addresses("GET_PREV_MCHUNK(mchunk_ptr)", &mchunk, GET_PREV_MCHUNK(&mchunk), "expect => -0x30 offset (-48 bytes)", STDOUT_FILENO);

    put_macro_with_relative_ptr_addresses("GET_MCHUNK_PTR(mchunk_data_ptr)", mchunk_data_ptr, GET_MCHUNK_PTR(mchunk_data_ptr), "expect => -0x30 offset (-48 bytes)", STDOUT_FILENO);
}

void    test_macros()
{
    put_colored(YELLOW, "TEST_MACROS", STDOUT_FILENO);

    test_macros_system();
    test_macros_mregion();
    test_macros_mchunk();
}
