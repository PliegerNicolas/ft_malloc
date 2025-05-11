/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend_mregion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:37:42 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:37:42 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    prepend_mregion(mregion_t **mregion, mregion_t *new_mregion)
{
    if (!mregion)
        return;

    if (*mregion != NULL)
    {
        new_mregion->next = *mregion;
        new_mregion->prev = NULL;
        (*mregion)->prev = new_mregion;
        *mregion = new_mregion;
    }
    else
        *mregion = new_mregion;
}