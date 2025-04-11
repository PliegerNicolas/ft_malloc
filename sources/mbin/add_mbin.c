/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_mbin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 20:02:08 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 20:02:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    append_mbin(mbin_t **mbin, mbin_t *new_mbin)
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

void    prepend_mbin(mbin_t **mbin, mbin_t *new_mbin)
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