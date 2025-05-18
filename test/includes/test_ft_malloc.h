/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_malloc.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:30:34 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:30:34 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FT_MALLOC_H
# define TEST_FT_MALLOC_H

# ifndef STD_MALLOC
#  define STD_MALLOC 0
# endif

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* For size_t */
# include <stddef.h>

/* For bool */
#include <stdbool.h>

/* For real malloc, realloc, free... */
#include <stdlib.h>

/* For printf */
# include <stdio.h>

/* libft_mini */
# include "libft_mini.h"

// For our custom malloc implementation.
#  include "ft_malloc.h"

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

# define RESET          "\033[0m"
# define BOLD           "\033[1m"
# define DIM            "\033[2m"
# define ITALIC         "\033[3m"
# define UNDERLINE      "\033[4m"
# define BLINK          "\033[5m"
# define REVERSE        "\033[7m"
# define HIDDEN         "\033[8m"
# define STRIKETHROUGH  "\033[9m"

# define BLACK          "\033[0;30m"
# define RED            "\033[0;31m"
# define GREEN          "\033[0;32m"
# define YELLOW         "\033[0;33m"
# define BLUE           "\033[0;34m"
# define PURPLE         "\033[0;35m"
# define CYAN           "\033[0;36m"
# define WHITE          "\033[0;37m"

# define DIM_BLACK      "\033[2;30m"
# define DIM_RED        "\033[2;31m"
# define DIM_GREEN      "\033[2;32m"
# define DIM_YELLOW     "\033[2;33m"
# define DIM_BLUE       "\033[2;34m"
# define DIM_PURPLE     "\033[2;35m"
# define DIM_CYAN       "\033[2;36m"
# define DIM_WHITE      "\033[2;37m"

# define BRIGHT_BLACK   "\033[90m"
# define BRIGHT_RED     "\033[91m"
# define BRIGHT_GREEN   "\033[92m"
# define BRIGHT_YELLOW  "\033[93m"
# define BRIGHT_BLUE    "\033[94m"
# define BRIGHT_PURPLE  "\033[95m"
# define BRIGHT_CYAN    "\033[96m"
# define BRIGHT_WHITE   "\033[97m"

# define BOLD_BLACK     "\033[1;30m"
# define BOLD_RED       "\033[1;31m"
# define BOLD_GREEN     "\033[1;32m"
# define BOLD_YELLOW    "\033[1;33m"
# define BOLD_BLUE      "\033[1;34m"
# define BOLD_PURPLE    "\033[1;35m"
# define BOLD_CYAN      "\033[1;36m"
# define BOLD_WHITE     "\033[1;37m"

# define BG_BLACK       "\033[40m"
# define BG_RED         "\033[41m"
# define BG_GREEN       "\033[42m"
# define BG_YELLOW      "\033[43m"
# define BG_BLUE        "\033[44m"
# define BG_PURPLE      "\033[45m"
# define BG_CYAN        "\033[46m"
# define BG_WHITE       "\033[47m"

# define BG_BRIGHT_BLACK    "\033[100m"
# define BG_BRIGHT_RED      "\033[101m"
# define BG_BRIGHT_GREEN    "\033[102m"
# define BG_BRIGHT_YELLOW   "\033[103m"
# define BG_BRIGHT_BLUE     "\033[104m"
# define BG_BRIGHT_PURPLE   "\033[105m"
# define BG_BRIGHT_CYAN     "\033[106m"
# define BG_BRIGHT_WHITE    "\033[107m"

# define BG_BOLD_BLACK  "\033[1;40m"
# define BG_BOLD_RED    "\033[1;41m"
# define BG_BOLD_GREEN  "\033[1;42m"
# define BG_BOLD_YELLOW "\033[1;43m"
# define BG_BOLD_BLUE   "\033[1;44m"
# define BG_BOLD_PURPLE "\033[1;45m"
# define BG_BOLD_CYAN   "\033[1;46m"
# define BG_BOLD_WHITE  "\033[1;47m"

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

void    put_colored(char *color, char *title, bool newline, int fd);

void    put_size_t(size_t n, const char *expected_value, int fd);
void    put_ptr(void *ptr, const char *expected_value, int fd);
void    put_relative_ptrs(void *ptr1, void *ptr2s, const char *expected_value, int fd);

void    please_show_alloc_mem();

void    test_free(int fd);
void    test_malloc(int fd);
void    test_realloc(int fd);
void    test_macros(int fd);
void    test_multithreading(int fd);

void    *check_free(const char *title, void *ptr, const char *expected_result, int fd);

#endif