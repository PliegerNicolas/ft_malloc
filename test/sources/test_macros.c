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

/* Utils */

static void test_macro_returning_size_t(char *macro_name, char *description, size_t macro_result)
{
    ft_putstr_fd("- ", 1);
    ft_putstr_fd(macro_name, 1);
    if (description != NULL)
    {
        ft_putstr_fd(" (", 1);
        ft_putstr_fd(description, 1);
        ft_putchar_fd(')', 1);
    }
    ft_putstr_fd(": ", 1);
    ft_putsize_t_base_fd(macro_result, "0123456789", 10, 1);
    ft_putchar_fd('\n', 1);
}

/* Tests */

static void test_marena_macros()
{
    write_title("Testing `marena_t` macros.", 1);

    test_macro_returning_size_t("DEFAULT_MAX_MARENAS", NULL, DEFAULT_MAX_MARENAS);
}

static void test_mbin_macros()
{
    write_title("Testing `mbin_t` macros.", 1);

    test_macro_returning_size_t("TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN", NULL, TARGET_MIN_ALLOCATIONS_PER_UNIFORM_MBIN);
    test_macro_returning_size_t("TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY", NULL, TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY);

    test_macro_returning_size_t("MBIN_METADATA_SIZE", NULL, MBIN_METADATA_SIZE);

    test_macro_returning_size_t("TINY_MBIN_SIZE", NULL, TINY_MBIN_SIZE);
    test_macro_returning_size_t("SMALL_MBIN_SIZE", NULL, SMALL_MBIN_SIZE);

    test_macro_returning_size_t("LARGE_MBIN_SIZE", "bytes_to_store = 0", LARGE_MBIN_SIZE(0));
    test_macro_returning_size_t("LARGE_MBIN_SIZE", "bytes_to_store = 4242", LARGE_MBIN_SIZE(4242));
    test_macro_returning_size_t("LARGE_MBIN_SIZE", "bytes_to_store = 123456789", LARGE_MBIN_SIZE(123456789));

    // test_macro_returning_size_t();
    // test_macro_returning_size_t();
    // GET_UNIFORM_MBIN_INITIAL_MCHUNK_PTR()
    // GET_NONUNIFORM_MBIN_INITIAL_MCHUNK_PTR()
}

static void test_mchunk_macros()
{
    write_title("Testing `mchunk_t` macros.", 1);

    test_macro_returning_size_t("TARGET_TINY_MCHUNK_DATA_SIZE", NULL, TARGET_TINY_MCHUNK_DATA_SIZE);
    test_macro_returning_size_t("TARGET_SMALL_MCHUNK_DATA_SIZE", NULL, TARGET_SMALL_MCHUNK_DATA_SIZE);

    test_macro_returning_size_t("MCHUNK_METADATA_SIZE", NULL, MCHUNK_METADATA_SIZE);

    test_macro_returning_size_t("TINY_MCHUNK_DATA_SIZE", NULL, TINY_MCHUNK_DATA_SIZE);
    test_macro_returning_size_t("SMALL_MCHUNK_DATA_SIZE", NULL, SMALL_MCHUNK_DATA_SIZE);

    test_macro_returning_size_t("TINY_MCHUNK_SIZE", NULL, TINY_MCHUNK_SIZE);
    test_macro_returning_size_t("SMALL_MCHUNK_SIZE", NULL, SMALL_MCHUNK_SIZE);

    test_macro_returning_size_t("LARGE_MCHUNK_DATA_SIZE", "bytes_to_store=0", LARGE_MCHUNK_DATA_SIZE(0));
    test_macro_returning_size_t("LARGE_MCHUNK_DATA_SIZE", "bytes_to_store=42", LARGE_MCHUNK_DATA_SIZE(42));

    mchunk_t    mchunk = {
        .state = FREE,
        .size = ALIGN_UP(50, MIN_ALIGNMENT_BOUNDARY),
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };
    // mchunk_t mchunk = {
    //     .
    //     // .state = FREE,
    //     // .size = ALIGN_UP(50, MIN_ALIGNMENT_BOUNDARY),
    //     // .prev_size = 0,
    //     // .next_free_mchunk = NULL,
    //     // .prev_free_mchunk = NULL,
    // };

    test_macro_returning_size_t("GET_MCHUNK_DATA_SIZE", "&mchunk", GET_MCHUNK_DATA_SIZE(&mchunk));

    // test_macro_returning_size_t();
    // test_macro_returning_size_t();
    // GET_UNIFORM_MCHUNK_DATA_PTR
    // GET_NONUNIFORM_MCHUNK_DATA_PTR
}

static void test_global_macros()
{
    write_title("Testing global macros.", 1);

    test_macro_returning_size_t("FAILURE", NULL, (size_t)FAILURE);

    test_macro_returning_size_t("PAGE_SIZE", NULL, PAGE_SIZE);

    test_macro_returning_size_t("MMAP_PROTECTIONS", NULL, MMAP_PROTECTIONS);
    test_macro_returning_size_t("MMAP_FLAGS", NULL, MMAP_FLAGS);

    test_macro_returning_size_t("ALIGN_UP", "(32, 32)", ALIGN_UP(32, 32));
    test_macro_returning_size_t("ALIGN_UP", "(33, 32)", ALIGN_UP(33, 32));
}

void    test_macros()
{
    test_marena_macros();
    test_mbin_macros();
    test_mchunk_macros();
    test_global_macros();
}
