/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:29:58 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:29:58 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t  ft_putptr_fd(void *ptr, int fd)
{
    uintptr_t   addr;
    size_t      count;

    if (!ptr)
        return ft_putstr_fd("(nil)", fd);

    addr = (uintptr_t)ptr;
    count = ft_putstr_fd("0x", fd);

    if (addr == 0)
        return count + ft_putchar_fd('0', fd);

    return count + ft_putbase_fd(addr, "0123456789abcdef", 16, fd);
};
