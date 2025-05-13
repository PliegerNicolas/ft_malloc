/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   please.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 20:59:48 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-21 20:59:48 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

// These functions wrap around functions that do only exist in my malloc implementation.
// This helps comparing tests with glibc malloc (cf. make std).

void    please_show_alloc_mem()
{
    #if STD_MALLOC == 0
    show_alloc_mem();
    #endif
}