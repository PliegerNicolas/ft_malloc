/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:03:57 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:03:57 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void test_mchunk_type_boundaries(int fd)
{
    void    *ptrs[5] = { NULL };

    put_colored(UNDERLINE, "Test mchunk boundary sizes:", true, fd);

    /* Operations */

    put_colored(BOLD_CYAN, "Operations:", true, fd);

    put_colored(BRIGHT_WHITE, "malloc(0)", true, fd);
    ptrs[0] = malloc(0);

    put_colored(BRIGHT_WHITE, "malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE)", true, fd);
    ptrs[1] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);
    put_colored(BRIGHT_WHITE, "malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1)", true, fd);
    ptrs[2] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1);

    put_colored(BRIGHT_WHITE, "malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE)", true, fd);
    ptrs[3] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE);
    put_colored(BRIGHT_WHITE, "malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1)", true, fd);
    ptrs[4] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1);

    /* Results */

    put_colored(BOLD_CYAN, "Results:", true, fd);

    please_show_alloc_mem();

    /* Clean up */

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

static void test_mchunk_edge_cases(int fd)
{
    void    *ptrs[6] = { NULL };

    put_colored(UNDERLINE, "Test mchunk boundary sizes:", true, fd);

    /* Operations */

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wuninitialized"
    #pragma GCC diagnostic ignored "-Wno-alloc-size-larger-than"

    put_colored(BOLD_CYAN, "Operations:", true, fd);

    put_colored(BRIGHT_WHITE, "malloc(0)", true, fd);
    ptrs[0] = malloc(0);

    put_colored(BRIGHT_WHITE, "malloc(PAGE_SIZE)", true, fd);
    ptrs[1] = malloc(PAGE_SIZE);
    put_colored(BRIGHT_WHITE, "malloc(PAGE_SIZE - 1)", true, fd);
    ptrs[2] = malloc(PAGE_SIZE - 1);

    put_colored(BRIGHT_WHITE, "malloc(SIZE_MAX)", true, fd);
    ptrs[3] = malloc(SIZE_MAX);
    put_colored(BRIGHT_WHITE, "malloc(SIZE_MAX / 2)", true, fd);
    ptrs[4] = malloc(SIZE_MAX / 2);

    put_colored(BRIGHT_WHITE, "malloc(MAX_ALLOCATION_SIZE)", true, fd);
    ptrs[5] = malloc(MAX_ALLOCATION_SIZE);

    #pragma GCC diagnostic pop

    /* Results */

    put_colored(BOLD_CYAN, "Results:", true, fd);

    please_show_alloc_mem();

    /* Clean up */

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_realloc(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:        realloc(void *ptr, size_t size)     ", true, fd);
}

// #include "test_ft_malloc.h"

// void    test_realloc()
// {
//     void    *ptrs[5];

//     ft_bzero(ptrs, sizeof(ptrs));

//     put_colored(YELLOW, "TEST REALLOC", STDOUT_FILENO);

//     put_colored(CYAN, "॰ show allocated memory before allocation", STDOUT_FILENO);
//     show_alloc_mem();

//     // Need to handle double frees.
//     ptrs[0] = realloc(NULL, 0);
//     ptrs[1] = realloc(NULL, 42);
//     ptrs[2] = realloc(NULL, 128);
//     ptrs[3] = realloc(NULL, 500);
//     ptrs[4] = realloc(NULL, 1000);

//     put_colored(CYAN, "॰ show allocated memory after allocation", STDOUT_FILENO);
//     show_alloc_mem();

//     for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         free(ptrs[i]);

//     put_colored(CYAN, "॰ show allocated memory after free", STDOUT_FILENO);
//     show_alloc_mem();
// }