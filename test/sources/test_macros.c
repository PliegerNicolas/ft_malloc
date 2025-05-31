/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 15:22:08 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 15:22:08 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void test_configurable_macros(int fd)
{
    put_title("MALLOC_DEBUG:", BOLD_CYAN, fd);
    put_expected_result("0 (false) or 1 (true)", fd);
    put_macro_result_size_t(MALLOC_DEBUG, fd);

    ft_putchar_fd('\n', fd);

    put_title("DESIRED_ALIGNMENT_BOUNDARY:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_ALIGNMENT_BOUNDARY, fd);

    ft_putchar_fd('\n', fd);

    put_title("DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE, fd);
    put_title("DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE, fd);

    ft_putchar_fd('\n', fd);
    
    put_title("DESIRED_MCHUNKS_PER_BOUND_MREGION:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_MCHUNKS_PER_BOUND_MREGION, fd);
    put_title("DESIRED_MCHUNKS_PER_UNBOUND_MREGION:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_MCHUNKS_PER_UNBOUND_MREGION, fd);

    ft_putchar_fd('\n', fd);
    
    put_title("DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE:", BOLD_CYAN, fd);
    put_macro_result_size_t(DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, fd);
}

static void test_formatted_configurable_macros(int fd)
{
    put_title("ALIGNMENT_BOUNDARY:", BOLD_CYAN, fd);
    put_expected_result("2ₙ", fd);
    put_macro_result_size_t(ALIGNMENT_BOUNDARY, fd);

    ft_putchar_fd('\n', fd);

    put_title("TINY_MCHUNK_MIN_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("0", fd);
    put_macro_result_size_t(TINY_MCHUNK_MIN_ALLOCATION_SIZE, fd);
    put_title("SMALL_MCHUNK_MIN_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("2ₙ + 1", fd);
    put_macro_result_size_t(SMALL_MCHUNK_MIN_ALLOCATION_SIZE, fd);
    put_title("LARGE_MCHUNK_MIN_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("2ₙ + 1", fd);
    put_macro_result_size_t(LARGE_MCHUNK_MIN_ALLOCATION_SIZE, fd);
    
    ft_putchar_fd('\n', fd);

    put_title("TINY_MCHUNK_MAX_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("2ₙ", fd);
    put_macro_result_size_t(TINY_MCHUNK_MAX_ALLOCATION_SIZE, fd);
    put_title("SMALL_MCHUNK_MAX_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("2ₙ", fd);
    put_macro_result_size_t(SMALL_MCHUNK_MAX_ALLOCATION_SIZE, fd);

    ft_putchar_fd('\n', fd);

    put_title("MCHUNKS_PER_BOUND_MREGION:", BOLD_CYAN, fd);
    put_expected_result("at least 100", fd);
    put_macro_result_size_t(MCHUNKS_PER_BOUND_MREGION, fd);
    put_title("MCHUNKS_PER_UNBOUND_MREGION:", BOLD_CYAN, fd);
    put_expected_result("at least 1", fd);
    put_macro_result_size_t(MCHUNKS_PER_UNBOUND_MREGION, fd);

    ft_putchar_fd('\n', fd);

    put_title("INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE:", BOLD_CYAN, fd);
    put_expected_result("at least 0", fd);
    put_macro_result_size_t(INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, fd);
}

static void test_plateform_dependent_macros(int fd)
{
    put_title("PAGE_SIZE:", BOLD_CYAN, fd);
    put_expected_result("2ₙ", fd);
    put_macro_result_size_t(PAGE_SIZE, fd);

    ft_putchar_fd('\n', fd);

    put_title("ALIGNMENT_BOUNDARY:", BOLD_CYAN, fd);
    put_expected_result("2ₙ", fd);
    put_macro_result_size_t(ALIGNMENT_BOUNDARY, fd);

    ft_putchar_fd('\n', fd);

    put_title("PAGE_ALIGNED_SIZE_MAX:", BOLD_CYAN, fd);
    put_expected_result("page aligned SIZE_MAX <=> (size_t)-1", fd);
    put_macro_result_size_t(PAGE_ALIGNED_SIZE_MAX, fd);

    ft_putchar_fd('\n', fd);

    put_title("MAX_ALLOCATION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("the biggest acceptable power of 2 relative to the current configuration and plateform", fd);
    put_macro_result_size_t(MAX_ALLOCATION_SIZE, fd);

    ft_putchar_fd('\n', fd);

    put_title("STATUS_SUCCESS:", BOLD_CYAN, fd);
    put_expected_result("an offset of -1 bytes", fd);
    put_ptr_comparison(NULL, STATUS_SUCCESS, fd);

    put_title("STATUS_FAILURE:", BOLD_CYAN, fd);
    put_expected_result("an offset of -2 bytes", fd);
    put_ptr_comparison(NULL, STATUS_FAILURE, fd);
}

static void test_utilitary_plateform_macros(int fd)
{
    put_title("IS_ALIGNED(0, 15):", BOLD_CYAN, fd);
    put_expected_result("1 (true)", fd);
    put_macro_result_size_t(IS_ALIGNED(0, 15), fd);
    put_title("IS_ALIGNED(1, 3):", BOLD_CYAN, fd);
    put_expected_result("0 (false)", fd);
    put_macro_result_size_t(IS_ALIGNED(1, 3), fd);
    put_title("IS_ALIGNED(16, 8):", BOLD_CYAN, fd);
    put_expected_result("1 (true)", fd);
    put_macro_result_size_t(IS_ALIGNED(16, 8), fd);

    ft_putchar_fd('\n', fd);

    put_title("CLAMP_MIN(0, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MIN(0, 15), fd);
    put_title("CLAMP_MIN(8, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MIN(8, 15), fd);
    put_title("CLAMP_MIN(15, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MIN(15, 15), fd);
    put_title("CLAMP_MIN(42, 15):", BOLD_CYAN, fd);
    put_expected_result("42", fd);
    put_macro_result_int(CLAMP_MIN(42, 15), fd);
    put_title("CLAMP_MIN(42, -15):", BOLD_CYAN, fd);
    put_expected_result("42", fd);
    put_macro_result_int(CLAMP_MIN(42, -15), fd);
    put_title("CLAMP_MIN(-42, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MIN(-42, 15), fd);

    ft_putchar_fd('\n', fd);

    put_title("CLAMP_MAX(0, 15):", BOLD_CYAN, fd);
    put_expected_result("0", fd);
    put_macro_result_int(CLAMP_MAX(0, 15), fd);
    put_title("CLAMP_MAX(8, 15):", BOLD_CYAN, fd);
    put_expected_result("8", fd);
    put_macro_result_int(CLAMP_MAX(8, 15), fd);
    put_title("CLAMP_MAX(15, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MAX(15, 15), fd);
    put_title("CLAMP_MAX(42, 15):", BOLD_CYAN, fd);
    put_expected_result("15", fd);
    put_macro_result_int(CLAMP_MAX(42, 15), fd);
    put_title("CLAMP_MAX(42, -15):", BOLD_CYAN, fd);
    put_expected_result("-15", fd);
    put_macro_result_int(CLAMP_MAX(42, -15), fd);
    put_title("CLAMP_MAX(-42, 15):", BOLD_CYAN, fd);
    put_expected_result("-42", fd);
    put_macro_result_int(CLAMP_MAX(-42, 15), fd);

    ft_putchar_fd('\n', fd);

    put_title("ALIGN_UP_POW2(0):", BOLD_CYAN, fd);
    put_expected_result("1", fd);
    put_macro_result_size_t(ALIGN_UP_POW2(0), fd);
    put_title("ALIGN_UP_POW2(1):", BOLD_CYAN, fd);
    put_expected_result("1", fd);
    put_macro_result_size_t(ALIGN_UP_POW2(1), fd);
    put_title("ALIGN_UP_POW2(2):", BOLD_CYAN, fd);
    put_expected_result("2", fd);
    put_macro_result_size_t(ALIGN_UP_POW2(2), fd);
    put_title("ALIGN_UP_POW2(20):", BOLD_CYAN, fd);
    put_expected_result("32", fd);
    put_macro_result_size_t(ALIGN_UP_POW2(20), fd);

    ft_putchar_fd('\n', fd);

    put_title("ALIGN_DOWN_POW2(0):", BOLD_CYAN, fd);
    put_expected_result("1", fd);
    put_macro_result_size_t(ALIGN_UP_POW2(0), fd);
    put_title("ALIGN_DOWN_POW2(1):", BOLD_CYAN, fd);
    put_expected_result("1", fd);
    put_macro_result_size_t(ALIGN_DOWN_POW2(1), fd);
    put_title("ALIGN_DOWN_POW2(2):", BOLD_CYAN, fd);
    put_expected_result("2", fd);
    put_macro_result_size_t(ALIGN_DOWN_POW2(2), fd);
    put_title("ALIGN_DOWN_POW2(20):", BOLD_CYAN, fd);
    put_expected_result("16", fd);
    put_macro_result_size_t(ALIGN_DOWN_POW2(20), fd);

    ft_putchar_fd('\n', fd);
    
    put_title("IS_POW_2(0):", BOLD_CYAN, fd);
    put_expected_result("0 (false)", fd);
    put_macro_result_size_t(IS_POW_2(0), fd);
    put_title("IS_POW_2(1):", BOLD_CYAN, fd);
    put_expected_result("1 (true)", fd);
    put_macro_result_size_t(IS_POW_2(1), fd);
    put_title("IS_POW_2(16):", BOLD_CYAN, fd);
    put_expected_result("1 (true)", fd);
    put_macro_result_size_t(IS_POW_2(16), fd);

    ft_putchar_fd('\n', fd);

    put_title("ALIGN_UP(0, 16):", BOLD_CYAN, fd);
    put_expected_result("0", fd);
    put_macro_result_size_t(ALIGN_UP(0, 16), fd);
    put_title("ALIGN_UP(1, 16):", BOLD_CYAN, fd);
    put_expected_result("16", fd);
    put_macro_result_size_t(ALIGN_UP(1, 16), fd);
    put_title("ALIGN_UP(16, 16):", BOLD_CYAN, fd);
    put_expected_result("16", fd);
    put_macro_result_size_t(ALIGN_UP(16, 16), fd);
    put_title("ALIGN_UP(17, 16):", BOLD_CYAN, fd);
    put_expected_result("32", fd);
    put_macro_result_size_t(ALIGN_UP(17, 16), fd);
    put_title("ALIGN_UP(17, 7):", BOLD_CYAN, fd);
    put_expected_result("Undefined behavior. `align` should be 2ₙ", fd);
    put_macro_result_size_t(ALIGN_UP(17, 7), fd);

    ft_putchar_fd('\n', fd);

    put_title("ALIGN_DOWN(0, 16):", BOLD_CYAN, fd);
    put_expected_result("0", fd);
    put_macro_result_size_t(ALIGN_DOWN(0, 16), fd);
    put_title("ALIGN_DOWN(1, 16):", BOLD_CYAN, fd);
    put_expected_result("0", fd);
    put_macro_result_size_t(ALIGN_DOWN(1, 16), fd);
    put_title("ALIGN_DOWN(16, 16):", BOLD_CYAN, fd);
    put_expected_result("16", fd);
    put_macro_result_size_t(ALIGN_DOWN(16, 16), fd);
    put_title("ALIGN_DOWN(17, 16):", BOLD_CYAN, fd);
    put_expected_result("16", fd);
    put_macro_result_size_t(ALIGN_DOWN(17, 16), fd);
    put_title("ALIGN_DOWN(17, 7):", BOLD_CYAN, fd);
    put_expected_result("Undefined behavior. `align` should be 2ₙ", fd);
    put_macro_result_size_t(ALIGN_DOWN(17, 7), fd);
}

void    test_mregion_macros(int fd)
{
    put_title("MREGION_HEADER_SIZE:", BOLD_CYAN, fd);
    put_expected_result("a multiple of ALIGNMENT_BOUNDARY", fd);
    put_macro_result_size_t(MREGION_HEADER_SIZE, fd);

    ft_putchar_fd('\n', fd);

    put_title("TINY_MREGION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("a multiple of PAGE_SIZE", fd);
    put_macro_result_size_t(TINY_MREGION_SIZE, fd);
    put_title("SMALL_MREGION_SIZE:", BOLD_CYAN, fd);
    put_expected_result("a multiple of PAGE_SIZE", fd);
    put_macro_result_size_t(SMALL_MREGION_SIZE, fd);
    put_title("LARGE_MREGION_SIZE(4200):", BOLD_CYAN, fd);
    put_expected_result("a multiple of PAGE_SIZE bigger or equal to `allocation_size`", fd);
    put_macro_result_size_t(LARGE_MREGION_SIZE(4200), fd);
}

void    test_utilitary_mregion_macros(int fd)
{
    mregion_t   mregion = {
        .mbin = &(mchunk_t) {
            .state = FREE,
            .allocation_size = PAGE_SIZE - MREGION_HEADER_SIZE - MCHUNK_HEADER_SIZE,
            .prev_allocation_size = 0,
            .next_free_mchunk = NULL,
            .prev_free_mchunk = NULL,
        },
        .next = NULL,
        .prev = NULL,
        .size = PAGE_SIZE,
        .used_mchunks = 1,
    };

    put_title("GET_MREGION_FIRST_MCHUNK(&mregion):", BOLD_CYAN, fd);
    put_expected_result("an offset of MREGION_HEADER_SIZE bytes", fd);
    put_ptr_comparison(&mregion, GET_MREGION_FIRST_MCHUNK(&mregion), fd);

    ft_putchar_fd('\n', fd);

    put_title("IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE):", BOLD_CYAN, fd);
    put_expected_result("1 (true)", fd);
    put_macro_result_int(IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE), fd);
    put_title("IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1):", BOLD_CYAN, fd);
    put_expected_result("0 (false)", fd);
    put_macro_result_int(IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1), fd);
}

void    test_mchunk_macros(int fd)
{
    put_title("MCHUNK_HEADER_SIZE:", BOLD_CYAN, fd);
    put_expected_result("a multiple of ALIGNMENT_BOUNDARY", fd);
    put_macro_result_size_t(MCHUNK_HEADER_SIZE, fd);
}

void    test_utilitary_mchunk_macros(int fd)
{
    mchunk_t    mchunk = {
        .state = FREE,
        .allocation_size = PAGE_SIZE - MREGION_HEADER_SIZE - MCHUNK_HEADER_SIZE,
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    put_title("GET_MCHUNK_SIZE(42):", BOLD_CYAN, fd);
    put_expected_result("MCHUNK_HEADER_SIZE + ALIGN_UP(42, ALIGNMENT_BOUNDARY)", fd);
    put_macro_result_size_t(GET_MCHUNK_SIZE(42), fd);
    put_title("GET_MCHUNK_SIZE(mchunk.allocation_size):", BOLD_CYAN, fd);
    put_expected_result("MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.allocation_size, ALIGNMENT_BOUNDARY)", fd);
    put_macro_result_size_t(GET_MCHUNK_SIZE(mchunk.allocation_size), fd);
    put_title("GET_MCHUNK_SIZE(mchunk.prev_allocation_size):", BOLD_CYAN, fd);
    put_expected_result("MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.prev_allocation_size, ALIGNMENT_BOUNDARY)", fd);
    put_macro_result_size_t(GET_MCHUNK_SIZE(mchunk.prev_allocation_size), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_MCHUNK_DATA_PTR(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of MCHUNK_HEADER_SIZE bytes", fd);
    put_ptr_comparison(&mchunk, GET_MCHUNK_DATA_PTR(&mchunk), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)):", BOLD_CYAN, fd);
    put_expected_result("an offset of -MCHUNK_HEADER_SIZE bytes", fd);
    put_ptr_comparison(GET_MCHUNK_DATA_PTR(&mchunk), GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_NEXT_MCHUNK(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of GET_MCHUNK_SIZE(mchunk.allocation_size) bytes", fd);
    put_ptr_comparison(&mchunk, GET_NEXT_MCHUNK(&mchunk), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_PREV_MCHUNK(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of -GET_MCHUNK_SIZE(mchunk.prev_allocation_size) bytes", fd);
    put_ptr_comparison(&mchunk, GET_PREV_MCHUNK(&mchunk), fd);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_macros(int fd)
{
    put_title("Testing:                                     macros                                     ", BG_BOLD_BLACK, fd);

    put_title("1.             configurable macros              ", BG_BLACK_BRIGHT_BLUE, fd);
    test_configurable_macros(fd);
    put_title("2.        formatted configurable macros         ", BG_BLACK_BRIGHT_BLUE, fd);
    test_formatted_configurable_macros(fd);

    put_title("3.          plateform dependent macros          ", BG_BLACK_BRIGHT_BLUE, fd);
    test_plateform_dependent_macros(fd);
    put_title("4.          utilitary plateform macros          ", BG_BLACK_BRIGHT_BLUE, fd);
    test_utilitary_plateform_macros(fd);

    put_title("4.               mregion macros                 ", BG_BLACK_BRIGHT_BLUE, fd);
    test_mregion_macros(fd);
    put_title("5.           utilitary mregion macros           ", BG_BLACK_BRIGHT_BLUE, fd);
    test_utilitary_mregion_macros(fd);

    put_title("6.                mchunk macros                 ", BG_BLACK_BRIGHT_BLUE, fd);
    test_mchunk_macros(fd);
    put_title("7.           utilitary mchunk macros            ", BG_BLACK_BRIGHT_BLUE, fd);
    test_utilitary_mchunk_macros(fd);
}
