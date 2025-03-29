/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 17:47:18 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 17:47:18 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t		ft_putendl_fd(char *s, int fd)
{
    if (!s)
        return 0;
    
    return ft_putstr_fd(s, fd) + ft_putchar_fd('\n', fd);
}