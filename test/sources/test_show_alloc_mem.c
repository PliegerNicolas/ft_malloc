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
    put_title(YELLOW, "૰ test_show_alloc_mem()", STDOUT_FILENO);

    show_alloc_mem();
}
