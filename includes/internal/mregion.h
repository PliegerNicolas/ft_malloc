/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mregion.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 12:38:36 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 12:38:36 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MREGION_H
# define MREGION_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "internal/macros.h"
# include "internal/mchunk.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @brief Enum of all the bound `mregion` categories.
 * @param TINY_MREGION_TYPE A `mregion` containing only `mchunk` of maximum `MCHUNK_TINY_MAX_ALLOCATION_SIZE` bytes.
 * @param SMALL_MREGION_TYPE A `mregion_t` containing only `mchunk` of maximum `MCHUNK_SMALL_MAX_ALLOCATION_SIZE` bytes.
 * @param NUM_BOUND_MREGION_TYPES Total number of bound `mregion_t`s.
*/
typedef enum e_bound_mregion_type
{
    TINY_MREGION_TYPE,
    SMALL_MREGION_TYPE,
    NUM_BOUND_MREGION_TYPES,
} bound_mregion_type_t;

/**
 * @brief A linked-list representing actual allocated data by the OS, also called a memory region.
 * Used as the header to a memory region.
 * 
 * @param size Size of the `mregion_t` (metadata included). In other words, the size requested to mmap().
 * @param mbin A collection of free `mchunk`s in the current `mregion_t`. For quicker lookups.
 * We do not keep the list of used `mchunk`s. Those pointers are in the hands of the user and will be returned to use later on.
 * @param used_mchunks Total used `mchunk_t`s.
 * @param next Next `mregion_t` in the linked list.
 * @param prev Previous `mregion_t` in the linked list.
 * 
 * @note The pointer returned by `mmap()` should be casted into a `mregion_t` struct.
*/
typedef struct s_mregion
{
    size_t              size;
    mchunk_t            *mbin;
    size_t              used_mchunks;

    struct s_mregion    *next;
    struct s_mregion    *prev;
} mregion_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
/* . */
status_t    init_mregion(mregion_t **mregion, size_t allocation_size);
status_t    init_mregions(mregion_t **mregion, size_t allocation_size, size_t mregions_count);

status_t    free_mregion(mregion_t **mregion, bool is_bound_mregion, size_t free_bound_mregion_threshold);
mregion_t   **get_mregion_by_mchunk(marena_t *marena, mchunk_t *mchunk, size_t allocation_size);

/* utils */
void        *mmap_mregion(size_t bytes);
status_t    munmap_mregion(mregion_t **mregion);

void        append_mregion(mregion_t **mregion, mregion_t *new_mregion);
void        prepend_mregion(mregion_t **mregion, mregion_t *new_mregion);

bool        is_on_mregion_boundary(mregion_t *mregion, mchunk_t *mchunk);
bool        does_mregion_contain_mchunk(mregion_t *mregion, mchunk_t *mchunk);
# pragma GCC visibility pop

#endif // MREGION_H
