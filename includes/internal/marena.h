/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marena.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 12:38:26 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 12:38:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARENA_H
# define MARENA_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "internal/macros.h"
# include "internal/mchunk.h"
# include "internal/mregion.h"

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @brief A memory management unit. It catalogues all categories of `mregion`s.
 * @param bounded_mregions A list of incrementally stored `mregion`s that only stored maximum n amount of bytes.
 * @param unbounded_mregion A list of incrementally stored `mregion`s that only stored maximum n amount of bytes.
*/
typedef struct s_marena
{
    mregion_t   *bound_mregions[NUM_BOUND_MREGIONS_CATEGORIES];
    mregion_t   *unbound_mregion;
} marena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
status_t    init_gmarena_once();

status_t    init_marena(marena_t *marena, size_t initial_mregions_per_bound_category);
status_t    init_marena_once(marena_t *marena, size_t initial_mregions_per_bound_category);

mregion_t   *find_marena_best_fit_mregion_head(marena_t *marena, size_t allocation_size);

mregion_t   **map_allocation_size_to_marena_mregion_head(marena_t *marena, size_t allocation_size);
# pragma GCC visibility pop

#endif // MARENA_H
