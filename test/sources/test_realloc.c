/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:54 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    test_realloc()
{
    void    *ptrs[4];

    ft_bzero(ptrs, sizeof(ptrs));

    put_colored(YELLOW, "TEST REALLOC", STDOUT_FILENO);

    put_colored(CYAN, "॰ show allocated memory before allocation", STDOUT_FILENO);
    show_alloc_mem();

    // Need to handle double frees.

    ptrs[0] = realloc(NULL, 500);
    ptrs[1] = realloc(ptrs[0], 200);
    // ptrs[0] = NULL;
    // ft_putendl_fd("-----------", STDOUT_FILENO);
    // show_alloc_mem();
    // ptrs[2] = realloc(NULL, 500);
    // ptrs[3] = realloc(ptrs[2], 499);
    // ptrs[2] = NULL;
    // ft_putendl_fd("----------", STDOUT_FILENO);
    // show_alloc_mem();
    // ptrs[1] = realloc(ptrs[0], 200);
    // ptrs[0] = NULL;
    // ptrs[0] = realloc(NULL, 84);
    // ft_putendl_fd("---", STDOUT_FILENO);
    // show_alloc_mem();
    // ptrs[1] = realloc(ptrs[0], 60);
    // ft_putendl_fd("---", STDOUT_FILENO);
    // show_alloc_mem();
    // ptrs[0] = NULL;
    // ptrs[0] = NULL;
    // ptrs[2] = realloc(ptrs[1], 1);
    // ptrs[1] = realloc(ptrs[0], 24);
    // ptrs[0] = malloc(42);
    // ptrs[1] = realloc(ptrs[0], 24);
    // ptrs[0] = realloc(NULL, 42);
    // ptrs[0] = realloc(NULL, 24);

    put_colored(CYAN, "॰ show allocated memory after allocation", STDOUT_FILENO);
    show_alloc_mem();

    free(ptrs[0]);
    free(ptrs[1]);
    // for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
    //     free(ptrs[i]);

    put_colored(CYAN, "॰ show allocated memory after free", STDOUT_FILENO);
    show_alloc_mem();
}