/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_to_best_fit_mregion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-22 21:16:20 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-22 21:16:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    iterate_to_best_fit_mregion(mregion_t **mregion)
{
    mregion_t   *current_mregion;

    if (!mregion)
        return;

    current_mregion = *mregion;
    while (current_mregion && current_mregion->mbin == NULL)
        current_mregion = current_mregion->next;
    *mregion = current_mregion;
}
