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

/** @brief Number of `mbin_subcategory_t` recognized as part of `mbin_category_t` `UNIFORM`.
 * @note 1 + [start_value] - [end_value]. */
# define NUM_UNIFORM_MBINS \
    (size_t)(1 + MBIN_SMALL - MBIN_TINY)
/** @brief Number of `mbin_subcategory_t` recognized as part of `mbin_category_t` `NON_UNIFORM`.
 * @note 1 + [start_value] - [end_value]. */
# define NUM_NON_UNIFORM_MBINS \
    (size_t)(1 + MBIN_LARGE - MBIN_LARGE)

/** @brief Get the index to the `marena_t`.`uniform_mbins` `mbin_t` per category. */
# define GET_UNIFORM_MBIN_INDEX(mbin_subcategory) \
    (size_t)(mbin_subcategory - MBIN_TINY)
/** @brief Get the index to the `marena_t`.`non_uniform_mbins` `mbin_t` per category. */
# define GET_NON_UNIFORM_MBIN_INDEX(mbin_subcategory) \
    (size_t)(mbin_subcategory - MBIN_LARGE)

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
     * @note Based on `NUM_UNIFORM_MBINS`. */
    mbin_t  *uniform_mbins[NUM_UNIFORM_MBINS];
    /** @brief A fixed-size array of pointers to non_uniform-`mbin_t` structures,
     * @note Based on `NUM_NON_UNIFORM_MBINS`. */
    mbin_t  *non_uniform_mbins[NUM_NON_UNIFORM_MBINS];
} marena_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

/* marena_t */

marena_t    marena_create(status_t *status);
size_t      marena_inspect(marena_t *marena, int fd);
void        marena_clear(marena_t *marena);

#endif
