/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsize_t_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:59:45 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:59:45 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t	ft_putsize_t_fd(size_t n, int fd)
{
    const char      *base = "0123456789";
    const size_t    base_len = 10;

    return ft_putsize_t_base_fd(n, base, base_len, fd);
}
