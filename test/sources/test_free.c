/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 17:49:16 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 17:49:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void test_free_edge_cases(int fd)
{
    run_in_thread(run_free_test, &(test_t) {
        .executed_test = "free(NULL)",
        .expected_res = "nothing",
        .ptr = NULL,
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_free_test, &(test_t) {
        .executed_test = "free((void*)-42)",
        .expected_res = "** free(): double free or corruption: 0xffffffffffffa6 **",
        .expected_err = true,
        .ptr = (void*)-42,
    });

    ft_putchar_fd('\n', fd);
    
    run_in_thread(run_double_free_test, &(test_t) {
        .executed_test = "free(ptr) * 2",
        .expected_res = "** free(): double free or corruption: 0x... **",
        .expected_err = true,
        .bytes = 42,
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_corrupted_free_test, &(test_t) {
        .executed_test = "free(ptr_with_corrupted_mchunk)",
        .expected_res = "** has_mchunk_aberrant_values(): corrupted mchunk: 0x...",
        .expected_err = true,
        .bytes = 42,
    });
}

static void test_mregion_free(int fd)
{
    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() completely one or more populated TINY mregion",
        .expected_res = "nothing",
        .size = 11,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.1 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.2 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.3 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.4 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.6 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.7 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.8 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.9 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() completely one or more populated SMALL mregion",
        .expected_res = "nothing",
        .size = 11,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.1 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.2 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.3 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.4 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.6 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.7 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.8 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.9 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() completely one or more populated LARGE mregions",
        .expected_res = "nothing",
        .size = 10,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 1 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 2 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 3 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 4 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 5 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 6 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 7 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 8 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 9 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 10 },
        },
    });
}

static void test_free_coalescing(int fd)
{
    void    *should_not_be_freed = (void*)0xDEADBEEF;

    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() pairs of mchunks",
        .expected_res = "No neighboring free mchunks.",
        .size = 11,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.1 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.2, .ptr = should_not_be_freed },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.3 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.4 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5, .ptr = should_not_be_freed },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.6 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.7 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.8, .ptr = should_not_be_freed },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.9 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() pairs of mchunks",
        .expected_res = "No neighboring free mchunks.",
        .size = 11,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.1 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.2 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.3, .ptr = should_not_be_freed },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.4 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.6, .ptr = should_not_be_freed },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.7 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.8 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.9, .ptr = should_not_be_freed },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_free_tests, &(tests_t) {
        .executed_test = "Free() pairs of mchunks",
        .expected_res = "No neighboring free mchunks.",
        .size = 10,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 1 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 2 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 3, .ptr = should_not_be_freed },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 4 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 5 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 6, .ptr = should_not_be_freed },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 7 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 8 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 9, .ptr = should_not_be_freed },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 10 },
        },
    });
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_free(int fd)
{
    put_title("Testing:                                 free(void *ptr)                                ", BG_BOLD_BLACK, fd);

    put_title("1.               free edge cases                ", BG_BLACK_BRIGHT_BLUE, fd);
    test_free_edge_cases(fd);

    put_title("2.                free mregion                  ", BG_BLACK_BRIGHT_BLUE, fd);
    test_mregion_free(fd);

    put_title("3.              free coalescing                 ", BG_BLACK_BRIGHT_BLUE, fd);
    test_free_coalescing(fd);
}