/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 01:28:31 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 01:28:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "internal/macros.h"
# include "internal/mchunk.h"
# include "internal/mregion.h"
# include "internal/marena.h"

/* libft_mini */
# include "libft_mini.h"

/* For NULL and size_t. */
# include <stddef.h>

/* For bool. */
# include <stdbool.h>

/* For mmap and munmap (man 2 mmap). */
# ifndef __USE_MISC
#  define __USE_MISC
# endif
# include <sys/mman.h>

/* For struct rlimit and getrlimit().  */
#include <sys/resource.h>

/* For all functions available in the library. */
# include <pthread.h>

/** For errno, ENOMEM... */
# include <errno.h>

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Global var */

extern marena_t gmarena;

/* Mandatory functions */

void        *malloc(size_t size);
void        *realloc(void *ptr, size_t size);
void        free(void *ptr);
void        show_alloc_mem();

/* Internal functions */

# pragma GCC visibility push(hidden)
status_t    init_gmarena_once();
size_t      get_max_mregion_size();
size_t      get_max_allocation_size(size_t allocation_size);

mchunk_t    **get_or_create_best_fit_free_mchunk(marena_t *marena, size_t allocation_size);
# pragma GCC visibility pop

#endif // FT_MALLOC_H
