/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mregions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 22:58:43 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 22:58:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

status_t    init_mregions(mregion_t **mregion, size_t mregion_size,  size_t total)
{
    mregion_t   *new_mregion;

    if (!mregion)
        return STATUS_FAILURE;

    for (size_t i = 0; i < total; i++)
    {
        new_mregion = NULL;
        if (init_mregion(&new_mregion, mregion_size) == STATUS_FAILURE)
            return STATUS_FAILURE;
        prepend_mregion(mregion, new_mregion);
    }

    return STATUS_SUCCESS;
}
