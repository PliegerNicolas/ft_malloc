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

//   -Waligned-new=[none|global|all] Warn even if 'new' uses a class member allocation function.
//   -Walloc-size-larger-than=<bytes> Warn for calls to allocation functions that attempt to allocate objects larger than the specified number of bytes.
//   -Walloc-zero                Warn for calls to allocation functions that specify zero bytes.
//   -Walloca                    Warn on any use of alloca.
//   -Walloca-larger-than=<number> Warn on unbounded uses of alloca, and on bounded uses of alloca whose bound can be larger than <number> bytes.
//   -Wanalyzer-allocation-size  Warn about code paths in which a pointer to a buffer is assigned to an incompatible type.
//   -Wanalyzer-malloc-leak      Warn about code paths in which a heap-allocated pointer leaks.
//   -Wanalyzer-mismatching-deallocation Warn about code paths in which the wrong deallocation function is called.
//   -Wanalyzer-tainted-allocation-size Warn about code paths in which an unsanitized value is used as an allocation size.
//   -Wmismatched-dealloc        Warn for deallocation calls with arguments returned from mismatched allocation functions.
//   -Wmismatched-new-delete     Warn for mismatches between calls to operator new or delete and the corresponding call to the allocation or deallocation function.
//   -Wno-alloc-size-larger-than Disable Walloc-size-larger-than= warning.  Equivalent to Walloc-size-larger-than=<SIZE_MAX> or larger.  Same as -Walloc-size-larger-than=.
//   -Wno-alloca-larger-than     Disable Walloca-larger-than= warning.  Equivalent to Walloca-larger-than=<SIZE_MAX> or larger.  Same as -Walloca-larger-than=.
//   -Wrealloc-lhs               Warn when a left-hand-side array variable is reallocated.
//   -Wrealloc-lhs-all           Warn when a left-hand-side variable is reallocated.
//   -Wsized-deallocation        Warn about missing sized deallocation functions.
//   -Wsuggest-attribute=malloc  Warn about functions which might be candidates for __attribute__((malloc)).
//   -Wuse-after-free            Warn for uses of pointers to deallocated storage.
//   -Wuse-after-free=<0,3>      Warn for uses of pointers to deallocated storage.


static void test_mchunk_edge_cases(int fd)
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wuninitialized"
    #pragma GCC diagnostic ignored "-Wno-alloc-size-larger-than"

    void    *ptrs[5] = { NULL };

    put_colored(UNDERLINE, "Test mchunk boundary sizes:", true, fd);

    put_colored(BRIGHT_WHITE, "malloc(-1)", true, fd);
    ptrs[0] = malloc(-1); // soucis ici, ça loop around et alloc une mregion de 4096 dans les macros.




    #pragma GCC diagnostic pop
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_malloc(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:            malloc(size_t size)             ", true, fd);

    test_mchunk_type_boundaries(fd);
    test_mchunk_edge_cases(fd);
}

// void    test_malloc()
// {
//     void *ptrs[8];

//     ft_bzero(ptrs, sizeof(ptrs));

//     put_colored(YELLOW, "TEST MALLOC", STDOUT_FILENO);

//     put_colored(CYAN, "॰ show allocated memory before allocation", STDOUT_FILENO);
//     show_alloc_mem();

//     ptrs[0] = malloc(0);
//     ptrs[1] = malloc(1);
//     ptrs[2] = malloc(42);

//     ptrs[3] = malloc(124);
//     ptrs[4] = malloc(442);

//     ptrs[5] = malloc(600);
//     ptrs[6] = malloc(1024);
//     ptrs[7] = malloc(2000);

//     put_colored(CYAN, "॰ show allocated memory after allocation", STDOUT_FILENO);
//     show_alloc_mem();

//     for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         free(ptrs[i]);

//     put_colored(CYAN, "॰ show allocated memory after free", STDOUT_FILENO);
//     show_alloc_mem();
// }
