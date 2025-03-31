/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 18:21:48 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-30 18:21:48 by nicolas          ###   ########.fr       */
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