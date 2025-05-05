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

/** @brief A pointer to function for finding the best `mchunk_t` from a `mregion_t`.
 * @note Useful to specify different search strategies. */
typedef mchunk_t **(*find_mregion_best_mchunk_fn_t)(mregion_t **mregion, size_t allocation_size);

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
size_t      show_alloc_mem_mchunks(mregion_t *mregion);

mchunk_t    **find_best_fit_free_mchunk(mregion_t **mregion, size_t allocation_size);
mchunk_t    *use_mchunk(mchunk_t **mchunk, size_t allocation_size);

bool        mchunk_has_aberrant_values(mchunk_t *mchunk);
mregion_t   *mchunk_find_corresponding_mregion(marena_t *marena, mchunk_t *mchunk);

status_t    free_mchunk(mregion_t *mregion, mchunk_t *mchunk);
/* Mappers */

# pragma GCC visibility pop

#endif // MCHUNK_H
