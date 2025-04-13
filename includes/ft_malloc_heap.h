
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

/* heap_t */

heap_t      heap_create(status_t *status);
size_t      heap_inspect(heap_t *heap, int fd);
void        heap_clear(heap_t *heap);

/* heap_t + mbin_t */

mbin_t      **mbin_select(heap_t *heap, mbin_category_t category, mbin_subcategory_t subcategory);
mbin_t      **mbin_fetch_or_create(heap_t *heap, size_t requested_bytes);

/* heap_t + mchunk_t */

void        *allocate_mchunk(heap_t *heap, size_t requested_bytes);
void        free_mchunk(heap_t *heap, void *ptr);

#endif
