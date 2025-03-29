/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 18:50:19 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 18:50:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t	ft_putint_fd(int n, int fd)
{
	size_t	count = 0;

	if (n == -2147483648)
		return ft_putint_fd((n / 10), fd) + ft_putint_fd(-(n % 10), fd);
	else
	{
		if (n < 0)
		{
			count += ft_putchar_fd('-', fd);
			n = -n;
		}
		if (n >= 10)
			count += ft_putint_fd(n / 10, fd) + ft_putint_fd(n % 10, fd);
		else
			count += ft_putchar_fd(n + '0', fd);
	}

	return count;
}
