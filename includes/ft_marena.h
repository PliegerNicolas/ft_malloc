/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_marena.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 21:47:40 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 21:47:40 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MARENA_H
# define FT_MARENA_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "macros.h"
# include "ft_mchunk.h"
# include "ft_mregion.h"

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
    mregion_t   *bounded_mregions[NUM_BOUNDED_MREGIONS_CATEGORIES];
    mregion_t   *unbounded_mregion;
} marena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* Internal functions */

# pragma GCC visibility push(hidden)
status_t    init_gmarena_once(marena_t *gmarena, size_t bounded_regions);
status_t    init_marena(marena_t *marena, size_t bounded_regions);
# pragma GCC visibility pop

#endif // FT_MARENA_H
