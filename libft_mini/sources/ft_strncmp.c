/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-16 20:03:09 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-16 20:03:09 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;
    unsigned char   c1;
    unsigned char   c2;

    i = 0;
    while (i < n && (s1[i] || s2[i]))
    {
        c1 = (unsigned char)s1[i];
        c2 = (unsigned char)s2[i];
        if (c1 != c2)
            return c1 - c2;
        i++;
    }

    return 0;
}