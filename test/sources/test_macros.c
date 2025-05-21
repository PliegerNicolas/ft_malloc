/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_macros.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:03:43 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:03:43 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void    test_configurable_macros(int fd)
{
    put_colored(UNDERLINE, "Configurable macros:", true, fd);

    put_colored(BOLD_CYAN, "MALLOC_DEBUG: ", false, fd);
    put_size_t(MALLOC_DEBUG, "0 || 1", fd);

    put_colored(BOLD_CYAN, "DESIRED_ALIGNMENT_BOUNDARY: ", false, fd);
    put_size_t(DESIRED_ALIGNMENT_BOUNDARY, "a power of 2, typically 16", fd);

    put_colored(BOLD_CYAN, "DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE: ", false, fd);
    put_size_t(DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE, "", fd);

    put_colored(BOLD_CYAN, "DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE: ", false, fd);
    put_size_t(DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "", fd);

    put_colored(BOLD_CYAN, "DESIRED_MCHUNKS_PER_BOUND_MREGION: ", false, fd);
    put_size_t(DESIRED_MCHUNKS_PER_BOUND_MREGION, "", fd);

    put_colored(BOLD_CYAN, "DESIRED_MCHUNKS_PER_UNBOUND_MREGION: ", false, fd);
    put_size_t(DESIRED_MCHUNKS_PER_UNBOUND_MREGION, "", fd);

    put_colored(BOLD_CYAN, "DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE: ", false, fd);
    put_size_t(DESIRED_INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, "", fd);
}

static void    test_system_macros(int fd)
{
    put_colored(UNDERLINE, "System macros:", true, fd);

    put_colored(BOLD_CYAN, "ALIGN_UP(17, 16): ", false, fd);
    put_size_t(ALIGN_UP(17, 16), "32", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP(0, 8): ", false, fd);
    put_size_t(ALIGN_UP(0, 8), "0", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP(4, 7): ", false, fd);
    put_size_t(ALIGN_UP(4, 7), "UB => {align} must be a power of 2", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP(8, -42): ", false, fd);
    put_size_t(ALIGN_UP(8, -42), "UB => {align} must be a power of 2", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP(-42, 16): ", false, fd);
    put_size_t(ALIGN_UP(-42, 16), "UB => {value} must be positive", fd);

    put_colored(BOLD_CYAN, "ALIGN_DOWN(35, 16): ", false, fd);
    put_size_t(ALIGN_DOWN(35, 16), "32", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN(0, 10): ", false, fd);
    put_size_t(ALIGN_DOWN(0, 0), "0", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN(4, 7): ", false, fd);
    put_size_t(ALIGN_DOWN(4, 7), "UB => {align} must be a power of 2", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN(8, -42): ", false, fd);
    put_size_t(ALIGN_DOWN(8, -42), "UB => {align} must be a power of 2", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN(-42, 16): ", false, fd);
    put_size_t(ALIGN_DOWN(-42, 16), "UB => {value} must be positive", fd);

    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(0): ", false, fd);
    put_size_t(ALIGN_UP_POW2(0), "1", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(1): ", false, fd);
    put_size_t(ALIGN_UP_POW2(1), "1", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(2): ", false, fd);
    put_size_t(ALIGN_UP_POW2(2), "2", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(5): ", false, fd);
    put_size_t(ALIGN_UP_POW2(5), "8", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(13): ", false, fd);
    put_size_t(ALIGN_UP_POW2(13), "16", fd);
    put_colored(BOLD_CYAN, "ALIGN_UP_POW2(50): ", false, fd);
    put_size_t(ALIGN_UP_POW2(50), "64", fd);

    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(0): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(0), "1", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(1): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(1), "1", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(2): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(2), "2", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(5): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(5), "4", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(13): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(13), "8", fd);
    put_colored(BOLD_CYAN, "ALIGN_DOWN_POW2(50): ", false, fd);
    put_size_t(ALIGN_DOWN_POW2(50), "32", fd);

    put_colored(BOLD_CYAN, "CLAMP_MIN(10, 15): ", false, fd);
    put_size_t(CLAMP_MIN(10, 15), "at least 15 => 15", fd);
    put_colored(BOLD_CYAN, "CLAMP_MIN(20, 15): ", false, fd);
    put_size_t(CLAMP_MIN(20, 15), "at least 15 => 20", fd);

    put_colored(BOLD_CYAN, "CLAMP_MAX(10, 15): ", false, fd);
    put_size_t(CLAMP_MAX(10, 15), "at max 15 => 10", fd);
    put_colored(BOLD_CYAN, "CLAMP_MAX(20, 15): ", false, fd);
    put_size_t(CLAMP_MAX(20, 15), "at max 15 => 15", fd);

    put_colored(BOLD_CYAN, "ALIGNMENT_BOUNDARY: ", false, fd);
    put_size_t(ALIGNMENT_BOUNDARY, "pow(DESIRED_ALIGNMENT_BOUNDARY, 2)", fd);

    put_colored(BOLD_CYAN, "IS_ALIGNED(1, 16): ", false, fd);
    put_size_t(IS_ALIGNED(1, 16), "0 <=> false", fd);
    put_colored(BOLD_CYAN, "IS_ALIGNED(32, 16): ", false, fd);
    put_size_t(IS_ALIGNED(32, 16), "1 <=> true", fd);
    put_colored(BOLD_CYAN, "IS_ALIGNED(-32, 16): ", false, fd);
    put_size_t(IS_ALIGNED(-32, 16), "UB => {value} must be positive", fd);
    put_colored(BOLD_CYAN, "IS_ALIGNED(32, -16): ", false, fd);
    put_size_t(IS_ALIGNED(32, -16), "UB => {align} must be a power of 2", fd);

    put_colored(BOLD_CYAN, "PAGE_SIZE: ", false, fd);
    put_size_t(PAGE_SIZE, "a power of 2, typically 4096 bytes", fd);
}

static void test_mregion_macros(int fd)
{
    put_colored(UNDERLINE, "Mregion macros:", true, fd);

    put_colored(BOLD_CYAN, "MCHUNKS_PER_BOUND_MREGION: ", false, fd);
    put_size_t(MCHUNKS_PER_BOUND_MREGION, "at least 100", fd);

    put_colored(BOLD_CYAN, "MCHUNKS_PER_UNBOUND_MREGION: ", false, fd);
    put_size_t(MCHUNKS_PER_UNBOUND_MREGION, "at least 1", fd);

    put_colored(BOLD_CYAN, "INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE: ", false, fd);
    put_size_t(INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE, "at least 0", fd);

    put_colored(BOLD_CYAN, "MREGION_HEADER_SIZE: ", false, fd);
    put_size_t(MREGION_HEADER_SIZE, "typically 48 bytes", fd);

    put_colored(BOLD_CYAN, "TINY_MREGION_SIZE: ", false, fd);
    put_size_t(TINY_MREGION_SIZE, "a PAGE_SIZE aligned value, typically 8192 bytes", fd);

    put_colored(BOLD_CYAN, "SMALL_MREGION_SIZE: ", false, fd);
    put_size_t(SMALL_MREGION_SIZE, "a PAGE_SIZE aligned value, typically 65536 bytes", fd);

    put_colored(BOLD_CYAN, "LARGE_MREGION_SIZE(20000): ", false, fd);
    put_size_t(LARGE_MREGION_SIZE(20000), "a PAGE_SIZE aligned value, typically 20480 bytes", fd);

    mregion_t   mregion = {
        .mbin = NULL,
        .next = NULL,
        .prev = NULL,
        .used_mchunks = 0,
        .size = SMALL_MREGION_SIZE, 
    };

    put_colored(BOLD_CYAN, "GET_MREGION_FIRST_MCHUNK(&mregion): ", false, fd);
    put_relative_ptrs(&mregion, GET_MREGION_FIRST_MCHUNK(&mregion), "an offset of MREGION_HEADER_SIZE bytes", fd);
}

static void test_mchunk_macros(int fd)
{
    put_colored(UNDERLINE, "Mchunk macros:", true, fd);

    put_colored(BOLD_CYAN, "MCHUNK_HEADER_SIZE: ", false, fd);
    put_size_t(MCHUNK_HEADER_SIZE, "typically 48 bytes", fd);

    put_colored(BOLD_CYAN, "GET_MCHUNK_SIZE(20): ", false, fd);
    put_size_t(GET_MCHUNK_SIZE(20), "typically 80 bytes", fd);

    mchunk_t    mchunk = {
        .state = USED,
        .allocation_size = 20,
        .prev_allocation_size = 0,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    put_colored(BOLD_CYAN, "GET_MCHUNK_DATA_PTR(&mchunk): ", false, fd);
    put_relative_ptrs(&mchunk, GET_MCHUNK_DATA_PTR(&mchunk), "an offset of MCHUNK_HEADER_SIZE bytes", fd);

    put_colored(BOLD_CYAN, "GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)): ", false, fd);
    put_relative_ptrs(GET_MCHUNK_DATA_PTR(&mchunk), GET_MCHUNK_PTR(GET_MCHUNK_DATA_PTR(&mchunk)), "an offset of -MCHUNK_HEADER_SIZE bytes", fd);

    put_colored(BOLD_CYAN, "TINY_MCHUNK_MAX_ALLOCATION_SIZE: ", false, fd);
    put_size_t(TINY_MCHUNK_MAX_ALLOCATION_SIZE, "DESIRED_TINY_MCHUNK_MAX_ALLOCATION_SIZE rounded to a power of 2, typically 64 bytes", fd);

    put_colored(BOLD_CYAN, "SMALL_MCHUNK_MAX_ALLOCATION_SIZE: ", false, fd);
    put_size_t(SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "DESIRED_SMALL_MCHUNK_MAX_ALLOCATION_SIZE rounded to a power of 2, typically 512 bytes", fd);

    put_colored(BOLD_CYAN, "GET_NEXT_MCHUNK(&mchunk): ", false, fd);
    put_relative_ptrs(&mchunk, GET_NEXT_MCHUNK(&mchunk), "an offset of 80 bytes", fd);

    put_colored(BOLD_CYAN, "GET_PREV_MCHUNK(&mchunk): ", false, fd);
    put_relative_ptrs(&mchunk, GET_PREV_MCHUNK(&mchunk), "an offset of -MCHUNK_HEADER_SIZE bytes, typically -48", fd);

    put_colored(BOLD_CYAN, "IS_BOUND_MREGION(50): ", false, fd);
    put_size_t(IS_BOUND_MREGION(50), "1 <=> true", fd);

    put_colored(BOLD_CYAN, "IS_BOUND_MREGION(5000): ", false, fd);
    put_size_t(IS_BOUND_MREGION(5000), "0 <=> false", fd);
}

static void test_other_macros(int fd)
{
    put_colored(UNDERLINE, "Other macros:", true, fd);

    put_colored(BOLD_CYAN, "PAGE_ALIGNED_SIZE_MAX: ", false, fd);
    put_size_t(PAGE_ALIGNED_SIZE_MAX, "a value close to SIZE_MAX", fd);

    put_colored(BOLD_CYAN, "MAX_ALLOCATION_SIZE: ", false, fd);
    put_size_t(MAX_ALLOCATION_SIZE, "a big value, I guess", fd);

    put_colored(BOLD_CYAN, "STATUS_SUCCESS: ", false, fd);
    put_ptr(STATUS_SUCCESS, "0xffffffffffffffff", fd);

    put_colored(BOLD_CYAN, "STATUS_FAILURE: ", false, fd);
    put_ptr(STATUS_FAILURE, "0xfffffffffffffffe", fd);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_macros(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:                macros.h                    ", true, fd);

    test_configurable_macros(fd);
    test_system_macros(fd);
    test_mregion_macros(fd);
    test_mchunk_macros(fd);
    test_other_macros(fd);
}
