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
 * @brief A memory management unit. It catalogues all types of `mregion`s.
 * @param bounded_mregions A list of incrementally stored `mregion`s that only stored maximum n amount of bytes.
 * @param unbounded_mregion A list of incrementally stored `mregion`s that only stored maximum n amount of bytes.
*/
typedef struct s_marena
{
    mregion_t   *bound_mregions[NUM_BOUND_MREGION_TYPES];
    mregion_t   *unbound_mregion;

    bool        initialized;
} marena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
/* . */
marena_t    *init_marena_once(marena_t *marena);
status_t    init_marena(marena_t *marena);
# pragma GCC visibility pop

#endif // MARENA_H
