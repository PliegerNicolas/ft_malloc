/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:49 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:49 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    test_malloc()
{
    void *ptrs[8];
    ft_bzero(ptrs, sizeof(ptrs));

    put_colored(YELLOW, "TEST MALLOC", STDOUT_FILENO);

    put_colored(CYAN, "॰ show allocated memory before allocation", STDOUT_FILENO);
    show_alloc_mem();

    ptrs[0] = malloc(0);
    ptrs[1] = malloc(1);
    ptrs[2] = malloc(42);

    ptrs[3] = malloc(124);
    ptrs[4] = malloc(442);

    ptrs[5] = malloc(600);
    ptrs[6] = malloc(1024);
    ptrs[7] = malloc(2000);

    put_colored(CYAN, "॰ show allocated memory after allocation", STDOUT_FILENO);
    show_alloc_mem();

    for (size_t i = 0; i < PTRS; i++)
        free(ptrs[i]);

    put_colored(CYAN, "॰ show allocated memory after free", STDOUT_FILENO);
    show_alloc_mem();
}
