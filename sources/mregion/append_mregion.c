/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_mregion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 22:36:34 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 22:36:34 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    append_mregion(mregion_t **mregion, mregion_t *new_mregion)
{
    mregion_t   *current_mregion;

    if  (!mregion)
        return;

    if (*mregion != NULL)
    {
        current_mregion = *mregion;
        while (current_mregion->next)
            current_mregion = current_mregion->next;
        current_mregion->next = new_mregion;
    }
    else
        *mregion = new_mregion;
}
