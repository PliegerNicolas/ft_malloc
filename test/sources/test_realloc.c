/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 17:42:12 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 17:42:12 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

//     // run_in_thread(run_chained_realloc_tests, &(tests_t) {
//     //     .test = "zigaga",
//     //     .expec_res = "zigogo",
//     //     .size = 5,
//     //     .values = (test_t[5]) {
//     //         { .bytes = 0 },
//     //         { .bytes = 1 },
//     //         { .bytes = 2 },
//     //         { .bytes = 3 },
//     //         { .bytes = 4 },
//     //     },
//     // });

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void test_realloc_semantic_special_cases(int fd)
{
    run_in_thread(run_realloc_test, &(test_t) {
        .executed_test = "realloc(NULL, 0)",
        .expected_res = "eq. malloc(0)",
        .bytes = 0,
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_test, &(test_t) {
        .executed_test = "realloc(NULL, 42)",
        .expected_res = "eq. malloc(42)",
        .bytes = 42,
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, 0)",
        .expected_res = "eq. free() of allocated ptr",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = 42 },
            { .bytes = 0 },
        },
    });
}





static void test_realloc_same_size(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 1.5 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 1.5 },
        },
    });
}





static void test_realloc_grow_between_mregions(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(max TINY mregion) => realloc(..., min SMALL mregion)",
        .expected_res = "Relocated mchunk from TINY mregion to SMALL mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(max SMALL mregion) => realloc(..., min LARGE mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to LARGE mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1 },
        },
    });
}

static void test_realloc_shrink_between_mregions(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(min LARGE mregion) => realloc(..., max SMALL mregion)",
        .expected_res = "Relocated mchunk from LARGE mregion to SMALL mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(min SMALL mregion) => realloc(..., max TINY mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to TINY mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_realloc(int fd)
{
    put_title("Testing:                        realloc(void *ptr, size_t size)                         ", BG_BOLD_BLACK, fd);

    put_title("1.        realloc semantic special cases        ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_semantic_special_cases(fd);

    put_title("2.               realloc same size              ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_same_size(fd);

    put_title("3.        realloc grow between mregions         ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_grow_between_mregions(fd);

    put_title("4.       realloc shrink between mregions        ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_shrink_between_mregions(fd);
}
