/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_marena.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 10:50:06 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 10:50:06 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/** @brief ... */
status_t    init_marena(marena_t *marena, size_t bounded_regions)
{
    mregion_t   **mregion;
    size_t      mregion_size;

    if (marena == NULL)
        return STATUS_FAILURE;

    ft_bzero(marena->bounded_mregions, sizeof(marena->bounded_mregions));
    for(bounded_mregion_category_t c = 0; c < NUM_BOUNDED_MREGIONS_CATEGORIES; c++)
    {
        mregion = &marena->bounded_mregions[c];
        mregion_size = map_bounded_mregion_category_to_mregion_size(c);
        if (init_mregions(mregion, mregion_size, NUM_INITIAL_BOUNDED_MREGIONS) == STATUS_FAILURE)
            return STATUS_FAILURE;
    }

    marena->unbounded_mregion = NULL;

    return STATUS_SUCCESS;
}
