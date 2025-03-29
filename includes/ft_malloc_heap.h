
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
# include "ft_malloc_arena.h"

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
    /** @brief Pointer to the head of a doubly-linked list of `arena_t` structures. */
    bool    is_initialized;

    /** @brief Pointer to the head of a doubly-linked list of `arena_t` structures. */
    arena_t arenas;

} heap_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

heap_t  initialize_heap();

#endif