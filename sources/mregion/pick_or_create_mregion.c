/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_or_create_mregion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-21 09:50:05 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-21 09:50:05 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   *pick_or_create_mregion(marena_t *marena, size_t allocation_size)
{
    mregion_t **mregion;

    mregion = map_allocation_size_to_existing_mregion(marena, allocation_size);
    if (!mregion)
        return STATUS_FAILURE;
    
    if (*mregion == NULL && init_mregion(mregion, map_allocation_size_to_mregion_size(allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return *mregion;
}
