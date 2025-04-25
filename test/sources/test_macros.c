/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-31 02:47:37 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-31 02:47:37 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    test_macros()
{
    const char      *base = "0123456789";
    const size_t    base_length = 10;

    put_title(YELLOW, "૰ test_heap_info_macros()", STDOUT_FILENO);

    put_title(PURPLE, "Configurable macros:", STDOUT_FILENO);
    put_size_t_macro("ALIGNMENT_BOUNDARY", ALIGNMENT_BOUNDARY, "Expect => 4, 8, 16, 32...", STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("MIN_MCHUNKS_PER_BOUNDED_MREGION", MIN_MCHUNKS_PER_BOUND_MREGION, "Expect => >=100", STDOUT_FILENO);
    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("TARGET_MCHUNK_TINY_MAX_DATA_SIZE", TARGET_MCHUNK_TINY_MAX_DATA_SIZE, "", STDOUT_FILENO);
    put_size_t_macro("TARGET_MCHUNK_SMALL_MAX_DATA_SIZE", TARGET_MCHUNK_SMALL_MAX_DATA_SIZE, "", STDOUT_FILENO);

    put_title(PURPLE, "Dynamic or const macros:", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(15, ALIGNMENT_BOUNDARY)", ALIGN_UP(15, ALIGNMENT_BOUNDARY), "Expect => 16 bytes", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(16, ALIGNMENT_BOUNDARY)", ALIGN_UP(16, ALIGNMENT_BOUNDARY), "Expect => 16 bytes", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(20, ALIGNMENT_BOUNDARY)", ALIGN_UP(20, ALIGNMENT_BOUNDARY), "Expect => 32 bytes", STDOUT_FILENO);
    put_size_t_macro("ALIGN_UP(32, ALIGNMENT_BOUNDARY)", ALIGN_UP(32, ALIGNMENT_BOUNDARY), "Expect => 32 bytes", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("PAGE_SIZE", PAGE_SIZE, "Expect => 4KB, 8KB...", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("MCHUNK_HEADER_PADDED_SIZE", MCHUNK_HEADER_PADDED_SIZE, "Expect => 32 bytes", STDOUT_FILENO);
    put_size_t_macro("MREGION_HEADER_PADDED_SIZE", MREGION_HEADER_PADDED_SIZE, "Expect => 4KB, 8KB...", STDOUT_FILENO);

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_size_t_macro("MCHUNK_TINY_MAX_DATA_SIZE", MCHUNK_TINY_MAX_DATA_SIZE, "Expect => 64 bytes", STDOUT_FILENO);
    put_size_t_macro("MCHUNK_SMALL_MAX_DATA_SIZE", MCHUNK_SMALL_MAX_DATA_SIZE, "Expect => 512 bytes", STDOUT_FILENO);
    
    /** mchunk_t ptr tests. */
    {
        mchunk_t    mchunk = { .prev_allocation_size = 16, .allocation_size = 32 };
        mchunk_t    *mchunk_ptr = &mchunk;

        ft_putchar_fd('\n', STDOUT_FILENO);
        put_macro_with_relative_ptr_addresses("GET_MCHUNK_DATA_PTR(mchunk_ptr)", mchunk_ptr, GET_MCHUNK_DATA_PTR(mchunk_ptr), "Expect => +0x20 offset (32 bytes)", STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        put_size_t_macro("GET_MCHUNK_PADDED_SIZE(mchunk_ptr)", GET_MCHUNK_PADDED_SIZE(mchunk_ptr), "Expect => 64 bytes", STDOUT_FILENO);
        put_size_t_macro("GET_PREV_MCHUNK_PADDED_SIZE(mchunk_ptr)", GET_PREV_MCHUNK_PADDED_SIZE(mchunk_ptr), "Expect => 48 bytes", STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        put_macro_with_relative_ptr_addresses("GET_NEXT_MCHUNK_PTR(mchunk_ptr)", mchunk_ptr, GET_NEXT_MCHUNK_PTR(mchunk_ptr), "Expect => +0x40 offset (64 bytes)", STDOUT_FILENO);
        put_macro_with_relative_ptr_addresses("GET_PREV_MCHUNK_PTR(mchunk_ptr)", mchunk_ptr, GET_PREV_MCHUNK_PTR(mchunk_ptr), "Expect => -0x30 offset (48 bytes)", STDOUT_FILENO);
    }

    ft_putchar_fd('\n', STDOUT_FILENO);
    put_ptr_macro("STATUS_SUCCESS", STATUS_SUCCESS, "Expect => 0xffffffffffffffff => (size_t)-1", STDOUT_FILENO);
    put_ptr_macro("STATUS_FAILURE", STATUS_FAILURE, "Expect => 0xfffffffffffffffe => (size_t)-2", STDOUT_FILENO);
}
