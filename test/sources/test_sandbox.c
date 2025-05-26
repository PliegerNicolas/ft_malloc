/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sandbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-26 11:52:46 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-26 11:52:46 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

// time -v ./tester sandbox

void    test_sandbox(int fd)
{
    int     i;
    char    *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        addr[0] = 42;
        free(addr);
        i++;
    }

    // please_show_alloc_mem();
}

// #define M (1024 * 1024)

// void    test_sandbox(int fd)
// {
//     char    *addr1;
//     char    *addr2;
//     char    *addr3;

//     addr1 = (char *)malloc(16 * M);
//     ft_memcpy(addr1, "Bonjour\0", 8);
//     ft_putendl_fd(addr1, STDOUT_FILENO);

//     addr2 = (char *)malloc(16 * M);

//     addr3 = (char *)realloc(addr1, 128 * M);
//     addr3[127 * M] = 42;
//     ft_putendl_fd(addr3, STDOUT_FILENO);

//     // please_show_alloc_mem();
// }
