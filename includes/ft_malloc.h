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

// https://gcc.gnu.org/onlinedocs/gcc/Thread-Local.html
extern __thread marena_t    gmarena;
extern pthread_mutex_t      gmutex;

/* Mandatory functions */

void        *malloc(size_t size);
void        *realloc(void *ptr, size_t size);
void        free(void *ptr);
void        show_alloc_mem();

/* Internal functions */

# pragma GCC visibility push(hidden)
/* . */
marena_t    *init_gmarena_once();

mchunk_t    *alloc_mchunk(marena_t *marena, size_t allocation_size);
mchunk_t    *realloc_mchunk(marena_t *marena, mchunk_t *used_mchunk, size_t reallocation_size);
mchunk_t    *free_mchunk_or_mregion(marena_t *marena, mchunk_t *mchunk);

size_t      print_marena(marena_t *marena, int fd, bool print_free);

status_t    gmutex_lock();
status_t    gmutex_unlock();
/* errors/ */
void        printerr(const char *caller, const char *err, void *ptr);

/* limits/ */
size_t      get_max_mregion_size();
size_t      get_max_allocation_size(size_t allocation_size);

/* mappings/ */
mregion_t   **map_allocation_size_to_marena_mregion_head(marena_t *marena, size_t allocation_size);
size_t      map_mregion_bound_type_to_max_allocation_size(bound_mregion_type_t bound_mregion_type);
size_t      map_allocation_size_to_mregion_size(size_t allocation_size);
const char  *map_mregion_bound_type_to_name(bound_mregion_type_t mregion_type);
# pragma GCC visibility pop

#endif // FT_MALLOC_H
