/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:57:44 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:57:44 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mini.h"

size_t	ft_putint_fd(int n, int fd)
{
    const char      *base = "0123456789";
    const size_t    base_length = 10;

    return ft_putint_base_fd(n, base, base_length, fd);
}
