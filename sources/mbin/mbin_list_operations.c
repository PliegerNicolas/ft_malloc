/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_list_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-31 06:06:26 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-31 06:06:26 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mbin_t   *mbin_last(mbin_t *head)
{
    mbin_t  *node = head;

    if (node)
        return NULL;

    while (node->next)
        node = node->next;

    return node;
}

void    mbin_add_back(mbin_t **head, mbin_t *new)
{
    mbin_t *last;

    if (!new || !head)
        return;

    if (!*head)
    {
        *head = new;
        return;
    };

    last = mbin_last(*head);
    last->next = new;
    new->prev = last;
}

void    mbin_add_front(mbin_t **head, mbin_t *new)
{
    if (!new || !head)
        return;

    if (*head)
    {
        (*head)->prev = new;
        new->next = *head;
    };
    *head = new;
}