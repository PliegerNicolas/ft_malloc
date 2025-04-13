/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_mbin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 19:51:53 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 19:51:53 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Append a `mbin_t` node to the end of an existing doubly-linked-list.
 * 
 * @note Can also set the first node.
*/
void    mbin_append(mbin_t **mbin, mbin_t *new_mbin)
{
    mbin_t  *node;

    if (!mbin || !new_mbin)
        return;

    if  (*mbin == NULL)
    {
        *mbin = new_mbin;

        new_mbin->next = NULL;
        new_mbin->prev = NULL;
    }
    else
    {
        node = *mbin;

        while(node->next)
            node = node->next;

        node->next = new_mbin;

        new_mbin->next = NULL;
        new_mbin->prev = node;
    };
}