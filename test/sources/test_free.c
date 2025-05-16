/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:04:21 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:04:21 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfree-nonheap-object"
#pragma GCC diagnostic ignored "-Wuninitialized"
#pragma GCC diagnostic ignored "-Wuse-after-free"
static void test_free_edge_cases(int fd)
{
    void    *ptrs[3] = { NULL };

    put_colored(UNDERLINE, "Test free edge cases:", true, fd);

    put_colored(BOLD_CYAN, "Operations:", true, fd);
    {
        for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
            ptrs[i] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);

        put_colored(BRIGHT_WHITE, "free(NULL): ", false, fd);
        free(NULL); ft_putchar_fd('\n', fd);
        ft_putendl_fd("🞄 Expected behavior: nothing.", fd);

        put_colored(BRIGHT_WHITE, "free(ptrs[0]); free(ptrs[0]): ", false, fd);
        free(ptrs[0]); free(ptrs[0]); ptrs[0] = NULL;
        ft_putendl_fd("🞄 Expected behavior: double free or corruption error message.", fd);

        void    *uninitialized_ptr;
        put_colored(BRIGHT_WHITE, "free(uninitialized_ptr): ", false, fd);
        free(uninitialized_ptr);
        ft_putendl_fd("🞄 Expected behavior: double free or corruption error message.", fd);

        int stack_var = 42;
        put_colored(BRIGHT_WHITE, "free(&stack_var): ", false, fd);
        free(&stack_var);
        ft_putendl_fd("🞄 Expected behavior: double free or corruption error message.", fd);

        put_colored(BRIGHT_WHITE, "ptrs[2] = realloc(ptrs[1]); free(ptrs[1]): ", false, fd);
        ptrs[2] = realloc(ptrs[1], TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1); free(ptrs[1]);
        ft_putendl_fd("🞄 Expected behavior: double free or corruption error message.", fd);
    }

    put_colored(BOLD_CYAN, "Results:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}
#pragma GCC diagnostic pop

static void test_coalesce_on_free(int fd)
{
    void    *ptrs[84] = { NULL };

    put_colored(UNDERLINE, "Test coalesce on free", true, fd);

    put_colored(BOLD_CYAN, "Operations:", true, fd);
    {
        for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
            ptrs[i++] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);

        please_show_alloc_mem();

        put_colored(BRIGHT_WHITE, "free(...ptrs[i % 3]): ", true, fd);
        free(ptrs[1]); ptrs[1] = NULL;
        // free(ptrs[2]); ptrs[2] = NULL;
        // for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        // {
        //     if (i % 3 != 0)
        //     {
        //         free(ptrs[i]);
        //         ptrs[i] = NULL;
        //     }
        // }
        // ft_putendl_fd("🞄 Expected behavior: no neighboring free `mchunk_t`s.", fd);

        le free ne semble pas trigger ici.
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

void    test_free(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:            free(void *ptr)                 ", true, fd);

    test_free_edge_cases(fd);
    test_coalesce_on_free(fd);
}
