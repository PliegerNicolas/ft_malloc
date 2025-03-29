/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 21:19:27 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 21:19:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void write_title(char *title, int fd)
{
    ft_putstr_fd(YELLOW, fd);
    ft_putstr_fd(title, fd);
    ft_putendl_fd(RESET, fd);
}