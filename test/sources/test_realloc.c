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
        .executed_test = "realloc(ptr, TINY_N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, SMALL_N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.5 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "realloc(ptr, LARGE_N) * 2",
        .expected_res = "no difference",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 1.5 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 1.5 },
        },
    });
}





static void test_realloc_grow_between_mregions(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, max TINY mregion) => realloc(..., min SMALL mregion)",
        .expected_res = "Relocated mchunk from TINY mregion to SMALL mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, max SMALL mregion) => realloc(..., min LARGE mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to LARGE mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, max TINY mregion) => realloc(..., min LARGE mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to LARGE mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });
}

static void test_realloc_shrink_between_mregions(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, min LARGE mregion) => realloc(..., max SMALL mregion)",
        .expected_res = "Relocated mchunk from LARGE mregion to SMALL mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, min SMALL mregion) => realloc(..., max TINY mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to TINY mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "malloc(NULL, min LARGE mregion) => realloc(..., max TINY mregion)",
        .expected_res = "Relocated mchunk from SMALL mregion to TINY mregion",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });
}

static void test_realloc_grow_in_place(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk to it's max alignment bounds",
        .expected_res = "In place grown mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = 0 + 1 },
            { .bytes = 0 + 1 },
            { .bytes = 0 + ALIGNMENT_BOUNDARY },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk to it's max alignment bounds",
        .expected_res = "In place grown mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE + ALIGNMENT_BOUNDARY },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk to it's max alignment bounds",
        .expected_res = "In place grown mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE + ALIGNMENT_BOUNDARY },
        },
    });
}

static void test_realloc_shrink_in_place(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Shrink mchunk to it's min alignment bounds",
        .expected_res = "In place shrunk mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = 0 + ALIGNMENT_BOUNDARY },
            { .bytes = 0 + 1 },
            { .bytes = 0 + 1 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Shrink mchunk to it's min alignment bounds",
        .expected_res = "In place shrunk mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE + ALIGNMENT_BOUNDARY },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Shrink mchunk to it's min alignment bounds",
        .expected_res = "In place shrunk mchunk (by ALIGNMENT_BOUNDARY - 1)",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE + ALIGNMENT_BOUNDARY },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });
}

static void test_realloc_grow_through_coalescing(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Min to max TINY mchunk growth through coalescing",
        .expected_res = "The same used TINY mchunk, with less or no available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Min to max SMALL mchunk growth through coalescing",
        .expected_res = "The same used SMALL mchunk, with less or no available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Min to next PAGE_SIZE aligned LARGE mchunk growth through coalescing",
        .expected_res = "Potentially another LARGE mchunk, and no available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = LARGE_MREGION_SIZE(LARGE_MCHUNK_MIN_ALLOCATION_SIZE) - MREGION_HEADER_SIZE - MCHUNK_HEADER_SIZE },
        },
    });
}

static void test_realloc_shrink_through_partitioning(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Max to min TINY mchunk shrinkage through partitioning/coalescing",
        .expected_res = "One used TINY mchunk, with more available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = 0 + 1 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Max to min SMALL mchunk shrinkage through partitioning/coalescing",
        .expected_res = "One used TINY mchunk, with more available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "N to min LARGE mchunk shrinkage through partitioning/coalescing",
        .expected_res = "One used LARGE mchunk, with available FREE space (used DEBUG mode to see FREE mchunks)",
        .size = 2,
        .values = (test_t[]) {
            { .bytes = LARGE_MREGION_SIZE(LARGE_MCHUNK_MIN_ALLOCATION_SIZE) - MREGION_HEADER_SIZE - MCHUNK_HEADER_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });
}

static void test_realloc_grow_with_blocking_neighbor(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk with USED neighbor",
        .expected_res = "A new USED mchunk while the previous one has been freed",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = 0 + 1 },
            { .bytes = 0 + 1 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk with USED neighbor",
        .expected_res = "A new USED mchunk while the previous one has been freed",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Grow mchunk with USED neighbor",
        .expected_res = "A new USED mchunk while the previous one has been freed",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = LARGE_MREGION_SIZE(LARGE_MCHUNK_MIN_ALLOCATION_SIZE) - MREGION_HEADER_SIZE - MCHUNK_HEADER_SIZE },
        },
    });
}

static void test_realloc_shrink_with_blocking_neighbor(int fd)
{
    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Shrink mchunk with USED neighbor",
        .expected_res = "A FREE mchunk stuck in between two used mchunks that didn't have any chance to get coalesced",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = 0 + 1 },
            { .bytes = 0 + 1 },
        },
    });

    ft_putchar_fd('\n', fd);

    run_in_thread(run_realloc_with_neighbor_test, &(tests_t) {
        .executed_test = "Shrink mchunk with USED neighbor",
        .expected_res = "A FREE mchunk stuck in between two used mchunks that didn't have any chance to get coalesced",
        .size = 3,
        .values = (test_t[]) {
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
        },
    });
}

static void test_realloc_chained_growth()
{
    run_in_thread(run_realloc_chained_tests, &(tests_t) {
        .executed_test = "A chain of growing allocations.",
        .expected_res = "One USED mchunk and no extra mregions (cf. MCHUNKS_PER_BOUND_MREGION AND MCHUNKS_PER_UNBOUND_MREGION).",
        .size = 15,
        .values = (test_t[]) {
            { .bytes = TINY_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.25 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.50 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.75 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },

            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.25 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.50 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.75 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },

            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.25 },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.50 },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.75 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42 },
        },
    });
}

static void test_realloc_chained_shrinkage()
{
    run_in_thread(run_realloc_chained_tests, &(tests_t) {
        .executed_test = "A chain of shrinking allocations.",
        .expected_res = "No USED mchunk and no extra mregions (cf. MCHUNKS_PER_BOUND_MREGION AND MCHUNKS_PER_UNBOUND_MREGION).",
        .size = 15,
        .values = (test_t[]) {
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42 },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.75 },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.50 },
            { .bytes = (LARGE_MCHUNK_MIN_ALLOCATION_SIZE * 42) * 0.25 },
            { .bytes = LARGE_MCHUNK_MIN_ALLOCATION_SIZE },

            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.75 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.50 },
            { .bytes = SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 0.25 },
            { .bytes = SMALL_MCHUNK_MIN_ALLOCATION_SIZE },

            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.75 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.50 },
            { .bytes = TINY_MCHUNK_MAX_ALLOCATION_SIZE * 0.25 },
            { .bytes = TINY_MCHUNK_MIN_ALLOCATION_SIZE },
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

    // Growth
    put_title("3.        realloc grow between mregions         ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_grow_between_mregions(fd);

    put_title("4.            realloc grow in place             ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_grow_in_place(fd);

    put_title("5.       realloc grow through coalescing        ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_grow_through_coalescing(fd);

    put_title("6.     realloc grow with blocking neighbor      ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_grow_with_blocking_neighbor(fd);

    put_title("7.           chained reallocs growth            ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_chained_growth();

    // Shrinkage
    put_title("8.       realloc shrink between mregions        ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_shrink_between_mregions(fd);

    put_title("9.           realloc shrink in place            ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_shrink_in_place(fd);

    put_title("10.     realloc shrink through partitioning      ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_shrink_through_partitioning(fd);

    put_title("11.    realloc shrink with blocking neighbor     ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_shrink_with_blocking_neighbor(fd);

    put_title("12.          chained reallocs shrinkage          ", BG_BLACK_BRIGHT_BLUE, fd);
    test_realloc_chained_shrinkage();
}
