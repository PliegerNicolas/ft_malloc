/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-27 09:46:49 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-27 09:46:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

// For NULL and size_t.
# include <stddef.h>

// For mmap and munmap (man 2 mmap).
# include <sys/mman.h>

// For getrlimit (man 2 getrlimit).
# include <sys/time.h>

// For all functions available in the library.
# include <pthread.h>

// Present in libft...
# include <unistd.h>

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Mandatory functions */

void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    free(void *ptr);

void    show_alloc_mem();

#endif