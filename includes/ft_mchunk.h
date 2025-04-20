/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mchunk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 21:50:53 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 21:50:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MCHUNK_H
# define FT_MCHUNK_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe headers. */
# include "macros.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @brief Represents a memory chunk within an `mregion`.
 * This structure acts as a header, placed directly before the user-allocatable memory.
 * 
 * @param prev_allocation_size Size of the previous `mchunk` allocated data. in memory (metadata, padding and user-allocatable memory included). 0 If none.
 * @param allocation_size Size of the current `mchunk` in memory (metadata, padding and user-allocatable memory included).
 * @param next_free_mchunk Used only when chunk is considered `FREE`. Else uninitalized or set to 0.
 * @param prev_free_mchunk Used only when chunk is considered `FREE`. Else uninitalized or set to 0.
 */
typedef struct s_mchunk
{
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
size_t  map_allocation_size_to_mchunk_size(size_t allocation_size);
# pragma GCC visibility pop

#endif // MCHUNK_H
