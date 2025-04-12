
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_heap.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:58:45 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:58:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_HEAP_H
# define FT_MALLOC_HEAP_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_marena.h"

/* For bool */
# include <stdbool.h>

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @struct s_heap
 * @brief Represents the dedicated heap structure, which manages a collection of arenas.
*/
typedef struct s_heap
{
    /** @brief Indicates if the `heap_t` has been initialized. */
    bool        is_initialized;

    /** @brief A memory arena. */
    marena_t    marena;
} heap_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

status_t    initialize_gheap(heap_t *gheap);
heap_t      new_heap(status_t *status);

void        show_heap(heap_t *heap, int fd);
void        clear_heap(heap_t *heap);

mchunk_t    *find_free_mchunk(heap_t *heap, size_t requested_data_size);

#endif
