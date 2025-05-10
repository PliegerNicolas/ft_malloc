/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_marena.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:18:26 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:18:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static status_t init_marena_bound_mregions(marena_t *marena)
{
    mregion_t   **current_mregion;
    size_t      max_allocation_size;

    if (!marena)
        return STATUS_FAILURE;

    for (bound_mregion_type_t type = 0; type < NUM_BOUND_MREGION_TYPES; type++)
    {
        max_allocation_size = map_mregion_bound_type_to_max_allocation_size(type);
        current_mregion = &(marena->bound_mregions[type]);

        if (init_mregions(current_mregion, max_allocation_size, INITIAL_MREGIONS_PER_BOUND_MREGION_TYPE) == STATUS_FAILURE)
            return STATUS_FAILURE;
    }

    return STATUS_SUCCESS;
}

static status_t init_marena_unbound_mregion(marena_t *marena)
{
    if (!marena)
        return STATUS_FAILURE;
    
    marena->unbound_mregion = NULL;

    return STATUS_SUCCESS;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

status_t    init_marena(marena_t *marena)
{
    if (!marena)
        return printerr("init_marena()", "Wrong parameters", NULL), STATUS_FAILURE;

    ft_bzero(marena, sizeof(*marena));
    
    if (init_marena_bound_mregions(marena) == STATUS_FAILURE)
        return STATUS_FAILURE;
    if (init_marena_unbound_mregion(marena) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return (marena->initialized = true), STATUS_SUCCESS;
}
