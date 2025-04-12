/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_marena.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 19:47:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-30 19:47:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MARENA_H
# define FT_MALLOC_MARENA_H

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_mbin.h"

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

# define MAX_MARENA

/* *************************************************************************** */
/* *                           CONFIGURABLE MACROS                           * */
/* *************************************************************************** */

/* CONSTANTS */

/** @brief Default maximum `marena_t`s.
 * @note Configurable arbitrary value. */
# define DEFAULT_MAX_MARENAS ((size_t)(8))

/* FUNCTIONS */

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @brief A memory arena.
 * @note Only one `marena_t` is defined per thread thus it can be defined on the stack.
*/
typedef struct s_marena
{
    /** @brief A fixed-size array of pointers to uniform-`mbin_t` structures,
     * @note Based on `NUM_UNIFORM_MBIN_SUBCATEGORIES`. */
    mbin_t  *uniform_mbins[NUM_MBIN_UNIFORM_SUBCATEGORIES];
    /** @brief A fixed-size array of pointers to non_uniform-`mbin_t` structures,
     * @note Based on `NUM_NON_UNIFORM_MBIN_SUBCATEGORIES`. */
    mbin_t  *non_uniform_mbins[NUM_MBIN_NON_UNIFORM_SUBCATEGORIES];
} marena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

marena_t    new_marena(status_t *status);

size_t      show_marena(marena_t *marena, int fd);
void        clear_marena(marena_t *marena);

#endif
