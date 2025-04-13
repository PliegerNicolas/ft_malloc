/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:07:03 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:07:03 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Deallocates and resets internal state of the given `mbin_t**`.
 * 
 * @note Does nothing if (*)mbin is NULL.
*/
void    mbin_clear(mbin_t **mbin)
{
    mbin_t  *node;
    mbin_t  *next;

    if (!mbin || !*mbin)
        return;

    node = *mbin;
    while (node)
    {
        next = node->next;
        munmap(node, node->size);
        node = next;
    };

    *mbin = NULL;
}