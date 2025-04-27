/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_show_alloc_mem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:58 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:58 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    test_show_alloc_mem()
{
    int *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7;

    put_title(YELLOW, "૰ test_show_alloc_mem()", STDOUT_FILENO);

    show_alloc_mem();

    ptr1 = malloc(42);
    ptr2 = malloc(43);
    ptr3 = malloc(44);

    ptr4 = malloc(442);
    ptr5 = malloc(443);

    ptr6 = malloc(20000);
    ptr7 = malloc(40112);

    show_alloc_mem();

    free(ptr1);
    free(ptr2);
    free(ptr3);

    free(ptr4);
    free(ptr5);

    free(ptr6);
    free(ptr7);
}
