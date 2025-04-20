/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mregion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 21:51:45 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 21:51:45 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MREGION_H
# define FT_MREGION_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "macros.h"
# include "ft_mchunk.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @brief Enum of all the bounded `mregion` categories.
 * @param TINY_MREGION A `mregion` containing only `mchunk` of maximum `MCHUNK_TINY_MAX_DATA_SIZE` bytes.
 * @param SMALL_MREGION A `mregion_t` containing only `mchunk` of maximum `MCHUNK_SMALL_MAX_DATA_SIZE` bytes.
 * @param NUM_BOUNDED_MREGIONS Total number of bounded `mregion_t`s.
*/
typedef enum e_bounded_mregion_category
{
    TINY_MREGION,
    SMALL_MREGION,
    NUM_BOUNDED_MREGIONS_CATEGORIES,
} bounded_mregion_category_t;

/**
 * @brief A linked-list representing actual allocated data by the OS, also called a memory region.
 * Used as the header to a memory region.
 * 
 * @param size Size of the `mregion_t` (metadata included). In other words, the size requested to mmap().
 * @param mbin A collection of free `mchunk`s in the current `mregion_t`. For quicker lookups.
 * We do not keep the list of used `mchunk`s. Those pointers are in the hands of the user and will be returned to use later on.
 * @param next Next `mregion_t` in the linked list.
 * 
 * @note The pointer returned by `mmap()` should be casted into a `mregion_t` struct.
*/
typedef struct s_mregion
{
    size_t              size;
    mchunk_t            *mbin;
    struct s_mregion    *next;
} mregion_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
status_t    init_mregion(mregion_t **mregion, size_t mregion_size);
status_t    init_mregions(mregion_t **mregion, size_t mregion_size,  size_t total);

void        append_mregion(mregion_t **mregion, mregion_t *new_mregion);
void        prepend_mregion(mregion_t **mregion, mregion_t *new_mregion);

mregion_t   *pick_or_create_mregion(marena_t *marena, size_t allocation_size);

mregion_t   **map_allocation_size_to_existing_mregion(marena_t *marena, size_t allocation_size);
size_t      map_allocation_size_to_mregion_size(size_t allocation_size);
size_t      map_bounded_mregion_category_to_mregion_size(bounded_mregion_category_t category);
# pragma GCC visibility pop

#endif // FT_MREGION_H
