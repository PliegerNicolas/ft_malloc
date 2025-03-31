/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-29 18:20:27 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-29 18:20:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_MINI_H
# define FT_LIBFT_MINI_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* For write and size_t */
# include <unistd.h>

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putstr_fd(char *s, int fd);
size_t		ft_putendl_fd(char *s, int fd);
size_t      ft_putint_fd(int n, int fd);
size_t      ft_putsize_t_fd(size_t n, int fd);

size_t		ft_strlen(const char *s);

void        *ft_memset(void *s, int c, size_t n);
void        ft_bzero(void *s, size_t n);

#endif