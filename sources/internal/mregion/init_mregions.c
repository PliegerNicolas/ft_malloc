/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 17:30:32 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-01 17:30:32 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

status_t    init_mregions(mregion_t **mregion, size_t allocation_size, size_t mregions_count)
{
    mregion_t   *new_mregion;

    if (!mregion)
        return printerr("init_mregions()", "Wrong parameters", NULL), STATUS_FAILURE;

    for (size_t i = 0; i< mregions_count; i++)
    {
        new_mregion = NULL;
        if (init_mregion(&new_mregion, allocation_size) == STATUS_FAILURE)
            return STATUS_FAILURE;
        prepend_mregion(mregion, new_mregion);
    }

    return STATUS_SUCCESS;
}
