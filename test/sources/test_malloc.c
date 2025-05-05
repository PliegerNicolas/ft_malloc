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

void    test_malloc(void *ptrs[PTRS])
{
    put_title(YELLOW, "૰ test_malloc()", STDOUT_FILENO);

    ptrs[0] = malloc(0);
    ptrs[1] = malloc(1);
    ptrs[2] = malloc(42);

    ptrs[3] = malloc(124);
    ptrs[4] = malloc(442);

    ptrs[5] = malloc(600);
    ptrs[6] = malloc(1024);
    ptrs[7] = malloc(2000);
}
