/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:29:51 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:29:51 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t		ft_putendl_fd(const char *s, int fd)
{
    if (!s)
        return 0;
    
    return ft_putstr_fd(s, fd) + ft_putchar_fd('\n', fd);
}