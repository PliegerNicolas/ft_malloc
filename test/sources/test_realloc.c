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
    void *ptrs[1];
    ft_bzero(ptrs, sizeof(ptrs));

    put_colored(YELLOW, "TEST REALLOC", STDOUT_FILENO);

    ptrs[0] = malloc(42);

    put_colored(CYAN, "॰ show allocated memory before allocation", STDOUT_FILENO);
    show_alloc_mem();

    ptrs[0] = realloc(ptrs[0], 24);
    ptrs[0] = realloc(ptrs[0], 42);

    put_colored(CYAN, "॰ show allocated memory after allocation", STDOUT_FILENO);
    show_alloc_mem();

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]);

    put_colored(CYAN, "॰ show allocated memory after free", STDOUT_FILENO);
    show_alloc_mem();
}