/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend_mbin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 19:52:01 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 19:52:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Prepend a `mbin_t` node to the end of an existing doubly-linked-list.
 * 
 * @note Can also set the first node.
*/
void    mbin_prepend(mbin_t **mbin, mbin_t *new_mbin)
{
    mbin_t  *node;

    if (!mbin || !new_mbin)
        return;

    if (*mbin == NULL)
    {
        *mbin = new_mbin;

        new_mbin->prev = NULL;
        new_mbin->next = NULL;
    }
    else
    {
        node = *mbin;
        
        node->prev = new_mbin;

        new_mbin->next = node;
        new_mbin->prev = NULL;

        *mbin = new_mbin;
    };
}