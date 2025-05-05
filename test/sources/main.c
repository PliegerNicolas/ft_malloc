/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:35 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:35 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

int main() {
    void *ptrs[8];

    ft_bzero(ptrs, sizeof(ptrs));

    test_macros();

    test_malloc(ptrs);
    test_show_alloc_mem();
    test_realloc(ptrs);
    show_alloc_mem();
    test_free(ptrs);
    show_alloc_mem();

    return (0);
}
