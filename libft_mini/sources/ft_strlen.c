/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:30:15 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:30:15 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t		ft_strlen(const char *s)
{
    size_t  len = 0;

    if (!s)
        return len;

    while (*s++)
        ++len;

    return len;
}