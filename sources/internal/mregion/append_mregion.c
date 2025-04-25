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

/**
 * @brief Appends a `mregion_t` node to the end of a `mregion_t` linked list.
 *
 * @param mregion Head of the linked list. If `NULL`, no action is taken.
 * @param new_mregion New node to append. If the list is empty, this becomes the head.
 *
 * @note If `mregion` is `NULL`, the function does nothing.
 *       If `*mregion` is `NULL`, `new_mregion` becomes the head of the list.
*/
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
