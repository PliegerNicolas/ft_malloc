/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:29:55 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:29:55 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t	ft_putint_base_fd(int n, const char *base, int base_len, int fd)
{
	size_t count = 0;

	if (base_len < 2)
		return count;

	if (n == INT_MIN)
		return ft_putint_base_fd((n / base_len), base, base_len, fd)
			+ ft_putint_base_fd(-(n % base_len), base, base_len, fd);

	if (n < 0)
	{
		n = -n;
		count += ft_putchar_fd('-', fd);
	};
	
	return count + ft_putbase_fd(n, base, base_len, fd);
}
