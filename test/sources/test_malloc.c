/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:03:47 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:03:47 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/* Utils */

static inline void  *validate_malloc(void *ptr, char *expected_result, int fd)
{
    if (ft_strncmp("PLDEP", expected_result, 4) == 0)
        ft_putendl_fd("plateform dependant ⚪", fd);
    else if (ft_strncmp("PTR", expected_result, 3) == 0 && ptr)
        ft_putendl_fd("success 🟢", fd);
    else if (ft_strncmp("NULL", expected_result, 4) == 0 && !ptr)
        ft_putendl_fd("success 🟢", fd);
    else
        ft_putendl_fd("failure 🔴", fd);
    return ptr;
}

/* Tests */

static void test_malloc_mchunk_type_boundaries(int fd)
{
    void    *ptrs[5] = { NULL };

    put_colored(UNDERLINE, "Test malloc mchunk boundary sizes:", true, fd);

    put_colored(BOLD_CYAN, "Operations:", true, fd);
    {
        put_colored(BRIGHT_WHITE, "malloc(0): ", false, fd);
        ptrs[0] = validate_malloc(malloc(0), "PTR", fd);
        put_colored(BRIGHT_WHITE, "malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE): ", false, fd);
        ptrs[1] = validate_malloc(malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE), "PTR", fd);

        put_colored(BRIGHT_WHITE, "malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1): ", false, fd);
        ptrs[2] = validate_malloc(malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1), "PTR", fd);
        put_colored(BRIGHT_WHITE, "malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE): ", false, fd);
        ptrs[3] = validate_malloc(malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE), "PTR", fd);

        put_colored(BRIGHT_WHITE, "malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1): ", false, fd);
        ptrs[4] = validate_malloc(malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1), "PTR", fd);
    }

    put_colored(BOLD_CYAN, "Results:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wno-alloc-size-larger-than"
static void test_malloc_edge_cases(int fd)
{
    void    *ptrs[6] = { NULL };

    put_colored(UNDERLINE, "Test malloc edge cases:", true, fd);

    put_colored(BOLD_CYAN, "Operations:", true, fd);
    {
        put_colored(BRIGHT_WHITE, "malloc(PAGE_SIZE - 1): ", false, fd);
        ptrs[0] = validate_malloc(malloc(PAGE_SIZE - 1), "PTR", fd);
        put_colored(BRIGHT_WHITE, "malloc(PAGE_SIZE): ", false, fd);
        ptrs[1] = validate_malloc(malloc(PAGE_SIZE), "PTR", fd);
        put_colored(BRIGHT_WHITE, "malloc(PAGE_SIZE + 1): ", false, fd);
        ptrs[2] = validate_malloc(malloc(PAGE_SIZE + 1), "PTR", fd);

        put_colored(BRIGHT_WHITE, "malloc(MAX_ALLOCATION_SIZE): ", false, fd);
        ptrs[3] = validate_malloc(malloc(MAX_ALLOCATION_SIZE), "PLDEP", fd);

        put_colored(BRIGHT_WHITE, "malloc(SIZE_MAX): ", false, fd);
        ptrs[4] = validate_malloc(malloc(SIZE_MAX), "NULL", fd);

        put_colored(BRIGHT_WHITE, "malloc(SIZE_MAX / 42): ", false, fd);
        ptrs[5] = validate_malloc(malloc(SIZE_MAX / 42), "PLDEP", fd);
    }

    put_colored(BOLD_CYAN, "Results:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}
#pragma GCC diagnostic pop

static void test_max_mchunks_per_mregion(int fd)
{
    void    *ptrs[425] = { NULL };

    put_colored(UNDERLINE, "Test max mchunks per mregion:", true, fd);

    put_colored(BOLD_CYAN, "Operations:", true, fd);
    {
        size_t  i = 0;

        put_colored(BRIGHT_WHITE, "200 * malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE): ", false, fd);
        while (i < 200)
            ptrs[i++] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);
        validate_malloc(NULL, "PLDEP", fd);

        put_colored(BRIGHT_WHITE, "200 * malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE): ", false, fd);
        while (i < 400)
            ptrs[i++] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE);
        validate_malloc(NULL, "PLDEP", fd);

        put_colored(BRIGHT_WHITE, "10 * malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1): ", false, fd);
        while (i < 410)
            ptrs[i++] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1);
        validate_malloc(NULL, "PLDEP", fd);
    }

    put_colored(BOLD_CYAN, "Results:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_malloc(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:            malloc(size_t size)             ", true, fd);

    test_malloc_edge_cases(fd);
    test_malloc_mchunk_type_boundaries(fd);
    test_max_mchunks_per_mregion(fd);
}
