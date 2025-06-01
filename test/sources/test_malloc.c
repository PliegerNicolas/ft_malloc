/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 00:03:26 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 00:03:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void test_malloc_around_small_sizes(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = 0 });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = 1 });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = 2 });
}

static void test_malloc_around_mchunk_header_size(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = MCHUNK_HEADER_SIZE - 1 });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = MCHUNK_HEADER_SIZE });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = MCHUNK_HEADER_SIZE + 1 });
}

static void test_malloc_around_alignment_boundary(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = ALIGNMENT_BOUNDARY - 1 });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = ALIGNMENT_BOUNDARY });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = ALIGNMENT_BOUNDARY + 1 });
}

static void test_malloc_around_page_size(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = PAGE_SIZE - 1 });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = PAGE_SIZE });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = PAGE_SIZE + 1 });
}

static void test_malloc_around_size_max(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "(nil) ** has_allocation_size_aberrant_value(): max allocation size exceeded **", .bytes = SIZE_MAX - 1, .expected_err = true });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "(nil) ** has_allocation_size_aberrant_value(): max allocation size exceeded **", .bytes = SIZE_MAX, .expected_err = true });
    ft_putchar_fd('\n', fd);
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = SIZE_MAX + 1 });
}

static void test_malloc_around_mregion_max_allocation_size(int fd)
{
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = 0 });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "0x...", .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "(nil) ** mmap_mregion(): Not enough memory (ENOMEM) **", .bytes = MAX_ALLOCATION_SIZE * 0.5, .expected_err = true });
    run_in_thread(run_malloc_test, &(test_t) { .expected_res = "(nil) ** mmap_mregion(): Not enough memory (ENOMEM) **", .bytes = MAX_ALLOCATION_SIZE, .expected_err = true });
}

static void test_fill_mregions(int fd)
{
    {
        test_t  tiny_mchunk_allocs[MCHUNKS_PER_BOUND_MREGION];

        for (size_t i = 0; i < MCHUNKS_PER_BOUND_MREGION; i++)
            tiny_mchunk_allocs[i].bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE;

        run_in_thread(run_malloc_tests, &(tests_t) {
            .executed_test = "MCHUNKS_PER_BOUND_MREGION * malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE)",
            .expected_res = "At least MCHUNKS_PER_BOUND_MREGION mchunks in one tiny mregion",
            .size = sizeof(tiny_mchunk_allocs) / sizeof(*tiny_mchunk_allocs),
            .values = tiny_mchunk_allocs,
        });
    }

    ft_putchar_fd('\n', fd);

    {
        test_t  small_mchunk_allocs[MCHUNKS_PER_BOUND_MREGION];

        for (size_t i = 0; i < MCHUNKS_PER_BOUND_MREGION; i++)
            small_mchunk_allocs[i].bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE;

        run_in_thread(run_malloc_tests, &(tests_t) {
            .executed_test = "MCHUNKS_PER_BOUND_MREGION * malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE)",
            .expected_res = "At least MCHUNKS_PER_BOUND_MREGION mchunks in one small mregion",
            .size = sizeof(small_mchunk_allocs) / sizeof(*small_mchunk_allocs),
            .values = small_mchunk_allocs,
        });
    }

    ft_putchar_fd('\n', fd);

    {
        test_t  large_mchunk_allocs[MCHUNKS_PER_UNBOUND_MREGION];

        for (size_t i = 0; i < MCHUNKS_PER_UNBOUND_MREGION; i++)
            large_mchunk_allocs[i].bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE;

        run_in_thread(run_malloc_tests, &(tests_t) {
            .executed_test = "MCHUNKS_PER_UNBOUND_MREGION * malloc(LARGE_MCHUNK_MIN_ALLOCATION_SIZE)",
            .expected_res = "At least MCHUNKS_PER_UNBOUND_MREGION mchunks in one large mregions",
            .size = sizeof(large_mchunk_allocs) / sizeof(*large_mchunk_allocs),
            .values = large_mchunk_allocs,
        });
    }
}

static void test_multi_mregion_mallocs()
{
    test_t  mchunk_allocs[10] = {
        { .bytes = 42 * 0 },
        { .bytes = 42 * 1 },
        { .bytes = 42 * 2 },
        { .bytes = 42 * 4 },
        { .bytes = 42 * 8 },
        { .bytes = 42 * 16 },
        { .bytes = 42 * 32 },
        { .bytes = 42 * 64 },
        { .bytes = 42 * 128 },
        { .bytes = 42 * 256 },
    };

    run_in_thread(run_malloc_tests, &(tests_t) {
        .executed_test = "10 * malloc(42 * n)",
        .expected_res = "Dispersed mchunks with sizes multiple of 42",
        .size = sizeof(mchunk_allocs) / sizeof(*mchunk_allocs),
        .values = mchunk_allocs,
    });
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_malloc(int fd)
{
    put_title("Testing:                               malloc(size_t size)                              ", BG_BOLD_BLACK, fd);
    
    // Single malloc calls
    put_title("1.           malloc(≈ SMALL_SIZES)            ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_small_sizes(fd);
    put_title("2.        malloc(≈ MCHUNK_HEADER_SIZE)         ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_mchunk_header_size(fd);
    put_title("3.        malloc(≈ ALIGNMENT_BOUNDARY)        ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_alignment_boundary(fd);
    put_title("4.            malloc(≈ PAGE_SIZE)             ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_page_size(fd);
    put_title("5.             malloc(≈ SIZE_MAX)             ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_size_max(fd);
    put_title("6.   malloc(≈ *_MCHUNK_MAX_ALLOCATION_SIZE)   ", BG_BLACK_BRIGHT_BLUE, fd);
    test_malloc_around_mregion_max_allocation_size(fd);

    // Bulk malloc calls
    put_title("7.            malloc: fill mregions             ", BG_BLACK_BRIGHT_BLUE, fd);
    test_fill_mregions(fd);
    put_title("8.         malloc: scatter in mregions          ", BG_BLACK_BRIGHT_BLUE, fd);
    test_multi_mregion_mallocs();
}
