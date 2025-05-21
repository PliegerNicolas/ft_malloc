/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clz_size_t.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 20:06:44 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-21 20:06:44 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

// Count leading zeroes

int ft_clz_size_t(size_t n)
{
    const int   bits = sizeof(n) * CHAR_BIT;

    for (int i = 0; i < bits; ++i)
        if ((n >> (bits - 1 - i)) & 1)
            return i;

    return bits;
}
