/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-27 11:49:56 by nicolas           #+#    #+#             */
/*   Updated: 2025/03/27 19:50:34 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

int main() {
    int *a = malloc(10);

    test_macros();

    test_free();
    test_malloc();
    test_realloc();

    test_show_alloc_mem();

    return (0);
}
