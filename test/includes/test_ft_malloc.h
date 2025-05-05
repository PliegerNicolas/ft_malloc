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

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

// For our custom malloc implementation.
# include "ft_malloc.h"

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

# define RESET          "\033[0m"
# define BOLD           "\033[1m"
# define ITALIC         "\033[3m"
# define UNDERLINE      "\033[4m"
# define STRIKETHROUGH  "\033[9m"

# define BLACK          "\033[0;30m"
# define RED            "\033[0;31m"
# define GREEN          "\033[0;32m"
# define YELLOW         "\033[0;33m"
# define BLUE           "\033[0;34m"
# define PURPLE         "\033[0;35m"
# define CYAN           "\033[0;36m"
# define WHITE          "\033[0;37m"

# define BOLD_BLACK     "\033[1;30m"
# define BOLD_RED       "\033[1;31m"
# define BOLD_GREEN     "\033[1;32m"
# define BOLD_YELLOW    "\033[1;33m"
# define BOLD_BLUE      "\033[1;34m"
# define BOLD_PURPLE    "\033[1;35m"
# define BOLD_CYAN      "\033[1;36m"
# define BOLD_WHITE     "\033[1;37m"

# define BG_BLACK       "\033[0;40m"
# define BG_RED         "\033[0;41m"
# define BG_GREEN       "\033[0;42m"
# define BG_YELLOW      "\033[0;43m"
# define BG_BLUE        "\033[0;44m"
# define BG_PURPLE      "\033[0;45m"
# define BG_CYAN        "\033[0;46m"
# define BG_WHITE       "\033[0;47m"

# define BOLD_BG_BLACK  "\033[1;40m"
# define BOLD_BG_RED    "\033[1;41m"
# define BOLD_BG_GREEN  "\033[1;42m"
# define BOLD_BG_YELLOW "\033[1;43m"
# define BOLD_BG_BLUE   "\033[1;44m"
# define BOLD_BG_PURPLE "\033[1;45m"
# define BOLD_BG_CYAN   "\033[1;46m"
# define BOLD_BG_WHITE  "\033[1;47m"



# define PTRS 8

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

void    put_title(char *color, char *title, int fd);
void    put_size_t_macro(char *title, size_t value, char *details, int fd);
void    put_ptr_macro(char *title, void *ptr, char *details, int fd);
void    put_macro_with_relative_ptr_addresses(char *title, void *src_ptr, void *dest_ptr, char *details, int fd);

void    test_macros();
void    test_malloc(void *ptrs[PTRS]);
void    test_realloc(void *ptrs[PTRS]);
void    test_free(void *ptrs[PTRS]);
void    test_show_alloc_mem();

#endif