/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunk.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 12:38:31 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 12:38:31 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MCHUNK_H
# define MCHUNK_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "internal/macros.h"

/* For size_t. */
# include <stddef.h>

/* For bool. */
# include <stdbool.h>

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

typedef enum e_usage_state
{
    FREE,
    USED,
    NUM_USAGE_STATES,
} usage_state_t;

/**
 * @brief Represents a memory chunk within an `mregion`.
 * This structure acts as a header, placed directly before the user-allocatable memory.
 * 
 * @param prev_allocation_size Size of the previous `mchunk` allocated data. in memory. 0 If none.
 * When manipulating this, do not forget about padding/alignment.
 * @param allocation_size Size of the current `mchunk` in memory.
 * When manipulating this, do not forget about padding/alignment.
 * @param next_free_mchunk Used only when chunk is considered `FREE`. Else uninitalized or set to 0.
 * @param prev_free_mchunk Used only when chunk is considered `FREE`. Else uninitalized or set to 0.
 */
typedef struct s_mchunk
{
    usage_state_t   state;

    size_t          prev_allocation_size;
    size_t          allocation_size;

    struct s_mchunk *next_free_mchunk;
    struct s_mchunk *prev_free_mchunk;
} mchunk_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
/* . */
mchunk_t    *select_best_fit_mbin_mchunk(mchunk_t *mbin, size_t allocation_size);

status_t    insert_free_mchunk_in_mregion_mbin(mregion_t *mregion, mchunk_t *free_mchunk);
mchunk_t    *migrate_mchunk_to_new_mregion(marena_t *marena, mchunk_t *original_mchunk, size_t reallocation_size);

mchunk_t    *use_mchunk(mregion_t **mregion, mchunk_t *original_mchunk, size_t allocation_size);
mchunk_t    *free_mchunk(mregion_t *mregion, mchunk_t *used_mchunk);

mchunk_t    *partition_mchunk(mregion_t **mregion, mchunk_t **original_mchunk, size_t new_allocation_size);
mchunk_t    *grow_mchunk(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size);
mchunk_t    *shrink_mchunk(marena_t *marena, mchunk_t *mchunk, size_t reallocation_size);
/* coalesce */
void        try_coalesce_with_next_free_mchunk(mregion_t *mregion, mchunk_t *mchunk);
void        try_coalesce_with_neighboring_free_mchunks(mregion_t *mregion, mchunk_t **mchunk);
bool        try_coalesce_until_allocation_size_reached(mregion_t *mregion, mchunk_t *mchunk, size_t target_size);
/* utils */
bool        has_mchunk_aberrant_values(mchunk_t *mchunk);
bool        has_allocation_size_aberrant_value(size_t allocation_size);
bool        is_mchunk_in_marena(marena_t *marena, mchunk_t *mchunk);
# pragma GCC visibility pop

#endif // MCHUNK_H
