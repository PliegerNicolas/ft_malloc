/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize_t_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 18:50:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 18:50:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t  ft_putsize_t_fd(size_t n, int fd)
{
    if (n >= 10)
        return ft_putsize_t_fd(n / 10, fd) + ft_putsize_t_fd(n % 10, fd);
    else
        return ft_putchar_fd(n + '0', fd);
}