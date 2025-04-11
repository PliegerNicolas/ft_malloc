/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_mbin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 19:32:49 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 19:32:49 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    clear_mbin(mbin_t **mbin)
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