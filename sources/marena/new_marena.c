/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_marena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 14:52:01 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-10 14:52:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/** @brief Initialize multiple `mbin_t`s in the doubly-linked list in one go. */
static mbin_t   *initialize_mbins(mbin_subcategory_t mbin_subcategory, size_t num_mbins)
{
    mbin_t  *initial_mbin;
    mbin_t  *next_mbin;
    size_t  mchunk_data_size;

    if (num_mbins == 0)
        return NULL;

    mchunk_data_size = get_mbin_subcategory_mchunk_data_size(mbin_subcategory, 0);

    initial_mbin = new_mbin(mchunk_data_size);
    if (initial_mbin == FAILURE)
        return FAILURE;
    
    for (size_t i = 0; i < num_mbins - 1; i++)
    {
        next_mbin = new_mbin(mchunk_data_size);
        if (next_mbin == FAILURE)
            return (clear_mbin(&initial_mbin), FAILURE);
        prepend_mbin(&initial_mbin,  next_mbin);
    };

    return initial_mbin;
};

/** @brief Create and initializes as new `marena_t`. */
marena_t    new_marena(status_t *status)
{
    marena_t    marena;
    mbin_t      *mbins;

    ft_bzero(marena.uniform_mbins, sizeof(marena.uniform_mbins));
    ft_bzero(marena.non_uniform_mbins, sizeof(marena.non_uniform_mbins));

    for (mbin_subcategory_t c = 0; c < NUM_UNIFORM_MBINS; c++)
    {
        marena.uniform_mbins[c] = initialize_mbins(c, TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY);
        if (marena.uniform_mbins[c] == FAILURE)
            return (*status = FAILURE, marena);
    };

    for (mbin_subcategory_t c = 0; c < NUM_NON_UNIFORM_MBINS; c++)
    {
        marena.non_uniform_mbins[c] = initialize_mbins(c, 0);
        if (marena.non_uniform_mbins[c] == FAILURE)
            return (*status = FAILURE, marena);
    };

    return (*status = SUCCESS, marena);
}