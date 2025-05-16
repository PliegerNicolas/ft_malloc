/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mchunk_in_marena.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 20:16:15 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 20:16:15 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    is_mchunk_in_marena(marena_t *marena, mchunk_t *mchunk)
{
    if (!marena)
        return false;
    else if (!mchunk)
        return true;

    for (bound_mregion_type_t type = 0; type < NUM_BOUND_MREGION_TYPES; type++)
        for (mregion_t *mregion = marena->bound_mregions[type]; mregion; mregion = mregion->next)
            if (does_mregion_contain_mchunk(mregion, mchunk))
                return true;

    for (mregion_t *mregion = marena->unbound_mregion; mregion; mregion = mregion->next)
        if (does_mregion_contain_mchunk(mregion, mchunk))
            return true;

    return false;
}
