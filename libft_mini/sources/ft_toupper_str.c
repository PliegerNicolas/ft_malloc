/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-18 14:24:58 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-18 14:24:58 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

char    *ft_toupper_str(char *str)
{
    char    *s;

    s = str;
    while (*s)
    {
        *s = ft_toupper((unsigned char)*s);
        ++s;
    }

    return str;
}