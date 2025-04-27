/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:29:45 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:29:45 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t  ft_putbase_fd(size_t n, const char *base, size_t base_len, int fd)
{
    size_t  count = 0;

    if (n >= base_len)
        count += ft_putbase_fd(n / base_len, base, base_len, fd);
    
    return count + ft_putchar_fd(base[n % base_len], fd);
}