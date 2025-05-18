/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-18 14:25:02 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-18 14:25:02 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char    *ft_tolower_str(char *str)
{
    char    *s;

    s = str;
    while (*s)
    {
        *s = ft_tolower((unsigned char)*s);
        ++s;
    }

    return str;
}
