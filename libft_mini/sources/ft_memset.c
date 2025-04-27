/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:29:41 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:29:41 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

void	*ft_memset(void *s, int c, size_t n)
{
    unsigned char   *ptr = s;
    unsigned char   value = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
        ptr[i] = value;

    return s;
}