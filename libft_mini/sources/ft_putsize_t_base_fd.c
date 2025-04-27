/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize_t_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:30:03 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:30:03 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t	ft_putsize_t_base_fd(size_t n, const char *base, size_t base_len, int fd)
{
	if (base_len < 2)
		return 0;

	return ft_putbase_fd(n, base, base_len, fd);
}
