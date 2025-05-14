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

// static void test_free_null(int fd)
// {
//     put_colored(UNDERLINE, "null:", true, fd);

//     put_colored(BOLD_CYAN, "free(NULL): ", false, fd);
//     free(NULL); ft_putchar_fd('\n', fd);
// }

// static void test_double_free(int fd)
// {
//     put_colored(UNDERLINE, "Double free:", true, fd);

//     put_colored(BOLD_CYAN, "free(NULL): ", false, fd);
//     free(NULL); ft_putchar_fd('\n', fd);
// }

// static void test_invalid_ptr(int fd)
// {
//     put_colored(UNDERLINE, "Invalid pointers:", true, fd);

//     #pragma GCC diagnostic push
//     #pragma GCC diagnostic ignored "-Wfree-nonheap-object"
//     #pragma GCC diagnostic ignored "-Wuninitialized"
//     #pragma GCC diagnostic ignored "-Wuse-after-free"



//     #pragma GCC diagnostic pop
// }


/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_free(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:            free(void *ptr)                 ", true, fd);
    
    // // This tells the compiler to ignore some rules that protect calls on free().
    // #pragma GCC diagnostic push
    // #pragma GCC diagnostic ignored "-Wfree-nonheap-object"
    // #pragma GCC diagnostic ignored "-Wuninitialized"
    // #pragma GCC diagnostic ignored "-Wuse-after-free"

    // void    *allocated_ptr;
    // void    *invalid_ptr = (void *)(uintptr_t)0xDEADBEEF;

    // put_colored(BOLD_CYAN, "free(NULL): ", false, fd);
    // free(NULL); ft_putchar_fd('\n', fd);
    // put_colored(BOLD_CYAN, "free(uninitialized_ptr): ", false, fd);
    // free(invalid_ptr);
    // put_colored(BOLD_CYAN, "free((void*)-1): ", false, fd);
    // free((void*)-1);
    
    // put_colored(BOLD_CYAN, "free(allocated_ptr): ", true, fd);

    // allocated_ptr = malloc(42);
    // put_colored(DIM, "After: malloc(42): ", true, fd);
    // please_show_alloc_mem();

    // put_colored(DIM, "After: free(allocated_Ptr): ", true, fd);
    // free(allocated_ptr);
    // please_show_alloc_mem();

    // put_colored(DIM, "After second: free(allocated_Ptr): ", false, fd);
    // free(allocated_ptr);

    // #pragma GCC diagnostic pop
}
