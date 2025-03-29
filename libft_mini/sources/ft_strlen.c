/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 17:53:20 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 17:53:20 by nicolas          ###   ########.fr       */
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