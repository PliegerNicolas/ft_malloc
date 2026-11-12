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
    TEST_MACRO(MALLOC_DEBUG, "0 (false) or 1 (true)", MALLOC_DEBUG == 0 || MALLOC_DEBUG == 1, fd);

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
    TEST_MACRO(ALIGNMENT_BOUNDARY, "2ₙ", IS_POW_2(ALIGNMENT_BOUNDARY), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_EQ(TINY_MCHUNK_MIN_ALLOCATION_SIZE, 0, fd);
    TEST_MACRO(SMALL_MCHUNK_MIN_ALLOCATION_SIZE, "2ₙ + 1", IS_POW_2((SMALL_MCHUNK_MIN_ALLOCATION_SIZE - 1)), fd);
    TEST_MACRO(LARGE_MCHUNK_MIN_ALLOCATION_SIZE, "2ₙ + 1", IS_POW_2((LARGE_MCHUNK_MIN_ALLOCATION_SIZE - 1)), fd);
    
    ft_putchar_fd('\n', fd);

    TEST_MACRO(TINY_MCHUNK_MAX_ALLOCATION_SIZE, "2ₙ", IS_POW_2(TINY_MCHUNK_MAX_ALLOCATION_SIZE), fd);
    TEST_MACRO(SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "2ₙ", IS_POW_2(SMALL_MCHUNK_MAX_ALLOCATION_SIZE), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(MCHUNKS_PER_BOUND_MREGION, "at least 100", MCHUNKS_PER_BOUND_MREGION >= 100, fd);
    TEST_MACRO(MCHUNKS_PER_UNBOUND_MREGION, "at least 1", MCHUNKS_PER_UNBOUND_MREGION >= 1, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, "at least 0", (long long)INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE >= 0, fd);
}

static void test_plateform_dependent_macros(int fd)
{
    TEST_MACRO(PAGE_SIZE, "2ₙ", IS_POW_2(PAGE_SIZE), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(ALIGNMENT_BOUNDARY, "2ₙ", IS_POW_2(ALIGNMENT_BOUNDARY), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(PAGE_ALIGNED_SIZE_MAX, "page aligned SIZE_MAX <=> (size_t)-1", IS_ALIGNED(PAGE_ALIGNED_SIZE_MAX, PAGE_SIZE) && SIZE_MAX - PAGE_ALIGNED_SIZE_MAX < PAGE_SIZE, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(MAX_ALLOCATION_SIZE, "the biggest acceptable power of 2 relative to the current configuration and plateform", IS_POW_2(MAX_ALLOCATION_SIZE), fd);

    ft_putchar_fd('\n', fd);

    put_title("STATUS_SUCCESS:", BOLD_CYAN, fd);
    put_expected_result("an offset of -1 bytes", fd);
    put_ptr_comparison(NULL, STATUS_SUCCESS, fd);
    put_check((size_t)STATUS_SUCCESS == (size_t)-1, fd);

    put_title("STATUS_FAILURE:", BOLD_CYAN, fd);
    put_expected_result("an offset of -2 bytes", fd);
    put_ptr_comparison(NULL, STATUS_FAILURE, fd);
    put_check((size_t)STATUS_FAILURE == (size_t)-2, fd);
}

static void test_utilitary_plateform_macros(int fd)
{
    TEST_MACRO_BOOL(IS_ALIGNED(0, 15), 1, fd);
    TEST_MACRO_BOOL(IS_ALIGNED(1, 3), 0, fd);
    TEST_MACRO_BOOL(IS_ALIGNED(16, 8), 1, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_INT_EQ(CLAMP_MIN(0, 15), 15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MIN(8, 15), 15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MIN(15, 15), 15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MIN(42, 15), 42, fd);
    TEST_MACRO_INT_EQ(CLAMP_MIN(42, -15), 42, fd);
    TEST_MACRO_INT_EQ(CLAMP_MIN(-42, 15), 15, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_INT_EQ(CLAMP_MAX(0, 15), 0, fd);
    TEST_MACRO_INT_EQ(CLAMP_MAX(8, 15), 8, fd);
    TEST_MACRO_INT_EQ(CLAMP_MAX(15, 15), 15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MAX(42, 15), 15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MAX(42, -15), -15, fd);
    TEST_MACRO_INT_EQ(CLAMP_MAX(-42, 15), -42, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_EQ(ALIGN_UP_POW2(0), 1, fd);
    TEST_MACRO_EQ(ALIGN_UP_POW2(1), 1, fd);
    TEST_MACRO_EQ(ALIGN_UP_POW2(2), 2, fd);
    TEST_MACRO_EQ(ALIGN_UP_POW2(20), 32, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_EQ(ALIGN_DOWN_POW2(0), 1, fd);
    TEST_MACRO_EQ(ALIGN_DOWN_POW2(1), 1, fd);
    TEST_MACRO_EQ(ALIGN_DOWN_POW2(2), 2, fd);
    TEST_MACRO_EQ(ALIGN_DOWN_POW2(20), 16, fd);

    ft_putchar_fd('\n', fd);
    
    TEST_MACRO_BOOL(IS_POW_2(0), 0, fd);
    TEST_MACRO_BOOL(IS_POW_2(1), 1, fd);
    TEST_MACRO_BOOL(IS_POW_2(16), 1, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_EQ(ALIGN_UP(0, 16), 0, fd);
    TEST_MACRO_EQ(ALIGN_UP(1, 16), 16, fd);
    TEST_MACRO_EQ(ALIGN_UP(16, 16), 16, fd);
    TEST_MACRO_EQ(ALIGN_UP(17, 16), 32, fd);
    put_title("ALIGN_UP(17, 7):", BOLD_CYAN, fd);
    put_expected_result("Undefined behavior. `align` should be 2ₙ", fd);
    put_macro_result_size_t(ALIGN_UP(17, 7), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_EQ(ALIGN_DOWN(0, 16), 0, fd);
    TEST_MACRO_EQ(ALIGN_DOWN(1, 16), 0, fd);
    TEST_MACRO_EQ(ALIGN_DOWN(16, 16), 16, fd);
    TEST_MACRO_EQ(ALIGN_DOWN(17, 16), 16, fd);
    put_title("ALIGN_DOWN(17, 7):", BOLD_CYAN, fd);
    put_expected_result("Undefined behavior. `align` should be 2ₙ", fd);
    put_macro_result_size_t(ALIGN_DOWN(17, 7), fd);
}

void    test_mregion_macros(int fd)
{
    TEST_MACRO(MREGION_HEADER_SIZE, "a multiple of ALIGNMENT_BOUNDARY", IS_ALIGNED(MREGION_HEADER_SIZE, ALIGNMENT_BOUNDARY), fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO(TINY_MREGION_SIZE, "a multiple of PAGE_SIZE", IS_ALIGNED(TINY_MREGION_SIZE, PAGE_SIZE), fd);
    TEST_MACRO(SMALL_MREGION_SIZE, "a multiple of PAGE_SIZE", IS_ALIGNED(SMALL_MREGION_SIZE, PAGE_SIZE), fd);
    TEST_MACRO(LARGE_MREGION_SIZE(4200), "a multiple of PAGE_SIZE bigger or equal to `allocation_size`", IS_ALIGNED(LARGE_MREGION_SIZE(4200), PAGE_SIZE) && LARGE_MREGION_SIZE(4200) >= 4200, fd);
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
    put_check((unsigned char *)GET_MREGION_FIRST_MCHUNK(&mregion) - (unsigned char *)&mregion == (long)MREGION_HEADER_SIZE, fd);

    ft_putchar_fd('\n', fd);

    TEST_MACRO_BOOL(IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE), 1, fd);
    TEST_MACRO_BOOL(IS_BOUND_MREGION(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1), 0, fd);
}

void    test_mchunk_macros(int fd)
{
    TEST_MACRO(MCHUNK_HEADER_SIZE, "a multiple of ALIGNMENT_BOUNDARY", IS_ALIGNED(MCHUNK_HEADER_SIZE, ALIGNMENT_BOUNDARY), fd);
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

    TEST_MACRO(GET_MCHUNK_SIZE(42), "MCHUNK_HEADER_SIZE + ALIGN_UP(42, ALIGNMENT_BOUNDARY)", GET_MCHUNK_SIZE(42) == MCHUNK_HEADER_SIZE + ALIGN_UP(42, ALIGNMENT_BOUNDARY), fd);
    TEST_MACRO(GET_MCHUNK_SIZE(mchunk.allocation_size), "MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.allocation_size, ALIGNMENT_BOUNDARY)", GET_MCHUNK_SIZE(mchunk.allocation_size) == MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.allocation_size, ALIGNMENT_BOUNDARY), fd);
    TEST_MACRO(GET_MCHUNK_SIZE(mchunk.prev_allocation_size), "MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.prev_allocation_size, ALIGNMENT_BOUNDARY)", GET_MCHUNK_SIZE(mchunk.prev_allocation_size) == MCHUNK_HEADER_SIZE + ALIGN_UP(mchunk.prev_allocation_size, ALIGNMENT_BOUNDARY), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_MCHUNK_DATA_PTR(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of MCHUNK_HEADER_SIZE bytes", fd);
    put_ptr_comparison(&mchunk, GET_MCHUNK_DATA_PTR(&mchunk), fd);
    put_check((unsigned char *)GET_MCHUNK_DATA_PTR(&mchunk) - (unsigned char *)&mchunk == (long)MCHUNK_HEADER_SIZE, fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)):", BOLD_CYAN, fd);
    put_expected_result("an offset of -MCHUNK_HEADER_SIZE bytes", fd);
    put_ptr_comparison(GET_MCHUNK_DATA_PTR(&mchunk), GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)), fd);
    put_check(GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)) == &mchunk, fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_NEXT_MCHUNK(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of GET_MCHUNK_SIZE(mchunk.allocation_size) bytes", fd);
    put_ptr_comparison(&mchunk, GET_NEXT_MCHUNK(&mchunk), fd);
    put_check((unsigned char *)GET_NEXT_MCHUNK(&mchunk) - (unsigned char *)&mchunk == (long)GET_MCHUNK_SIZE(mchunk.allocation_size), fd);

    ft_putchar_fd('\n', fd);

    put_title("GET_PREV_MCHUNK(&mchunk):", BOLD_CYAN, fd);
    put_expected_result("an offset of -GET_MCHUNK_SIZE(mchunk.prev_allocation_size) bytes", fd);
    put_ptr_comparison(&mchunk, GET_PREV_MCHUNK(&mchunk), fd);
    put_check((unsigned char *)&mchunk - (unsigned char *)GET_PREV_MCHUNK(&mchunk) == (long)GET_MCHUNK_SIZE(mchunk.prev_allocation_size), fd);
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
