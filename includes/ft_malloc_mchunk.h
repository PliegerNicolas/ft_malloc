/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_chunk.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-28 19:24:43 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-28 19:24:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MCHUNK_H
# define FT_MALLOC_MCHUNK_H

/* *************************************************************************** */
/* *                          GENERAL DOCUMENTATION                          * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                 INCLUDES                                * */
/* *************************************************************************** */

/* Annexe ft_malloc headers. */
# include "ft_malloc_macros.h"

/* For size_t. */
# include <stddef.h>

/* *************************************************************************** */
/* *                                  MACROS                                 * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                  MODELS                                 * */
/* *************************************************************************** */

/**
 * @enum e_mchunk_state
 * @brief Enumeration representing the supported `mchunk_t` states.
 *
 * These categories are used to identify the state of a `mchunk_t`.
*/
enum e_mchunk_state {
    /** @brief Chunk is marked as free (either freed or never used). */
    FREE,
    
    /** @brief Chunk is marked as in use. */
    IN_USE,
};

/**
 * @struct s_mchunk
 * @brief Metadata that provides information about the stored user data.
 *
 * The user data is stored immediately after the `mchunk_t` structure in memory,
 * within the corresponding `mbin_t` region.
 */
typedef struct s_mchunk
{
    /**
     * @brief Size of the stored data.
     * The data is located immediately after the `mchunk_t` structure in memory,
     * within the corresponding `mbin_t` region.
     */
    size_t stored_data_size;

    /** @brief The current state of the memory chunk. */
    enum e_mchunk_state state;
} mchunk_t;

/* *************************************************************************** */
/* *                                PROTOTYPES                               * */
/* *************************************************************************** */

#endif