/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   please_show_alloc_mem.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:06:40 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:06:40 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    please_show_alloc_mem()
{
    #if STD_MALLOC == 0
    show_alloc_mem();
    #endif
}