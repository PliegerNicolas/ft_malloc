/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend_mregion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:27:26 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:27:26 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    prepend_mregion(mregion_t **mregion, mregion_t *new_mregion)
{
    mregion_t   *current_mregion;

    if (!mregion)
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
