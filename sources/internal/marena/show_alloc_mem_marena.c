/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_marena.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:27:07 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:27:07 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static size_t   show_alloc_mem_marena_bound_mregions(marena_t *marena)
{
    size_t  total_allocated_bytes;

    if (!marena)
        return 0;

    total_allocated_bytes = 0;
    for (bound_mregion_type_t type = 0; type < NUM_BOUND_MREGION_TYPES; type++)
        total_allocated_bytes += show_alloc_mem_mregion(marena->bound_mregions[type], map_mregion_bound_type_to_name(type));

    return total_allocated_bytes;
}

static size_t   show_alloc_mem_marena_unbound_mregion(marena_t *marena)
{
    if (!marena)
        return 0;

    return show_alloc_mem_mregion(marena->unbound_mregion, "LARGE");
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

size_t  show_alloc_mem_marena(marena_t *marena)
{
    if (!marena)
        return 0;

    return show_alloc_mem_marena_bound_mregions(marena) + show_alloc_mem_marena_unbound_mregion(marena);
}