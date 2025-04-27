/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:30:26 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:30:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_MINI_H
# define FT_LIBFT_MINI_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* For write and size_t */
# include <unistd.h>

/* For uinptr_t */
#include <stdint.h>

/* For INT_MIN */
#include <limits.h>

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

size_t		ft_putchar_fd(char c, int fd);
size_t		ft_putstr_fd(char *s, int fd);
size_t		ft_putendl_fd(char *s, int fd);
size_t      ft_putint_fd(int n, int fd);
size_t      ft_putsize_t_fd(size_t n, int fd);
size_t      ft_putint_base_fd(int n, const char *base, int base_len, int fd);
size_t      ft_putsize_t_base_fd(size_t n, const char *base, size_t base_len, int fd);
size_t      ft_putbase_fd(size_t n, const char *base, size_t base_len, int fd);
size_t      ft_putptr_fd(void *ptr, int fd);

size_t		ft_strlen(const char *s);

void        *ft_memset(void *s, int c, size_t n);
void        ft_bzero(void *s, size_t n);

#endif