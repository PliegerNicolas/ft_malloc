/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marena.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 21:48:21 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-30 21:48:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// /**
//  * @brief Counts the number of nodes in a `marena_t`.
//  * 
//  * @param head Pointer to the head of the `marena_t` doubly-linked-list.
// */
// size_t  marena_size(marena_t *head)
// {
//     size_t count = 0;

//     for (marena_t *node = head; node; node = node->next)
//         ++count;

//     return count;
// }

// /**
//  * @brief Returns the last node of a `marena_t`.
//  * 
//  * @param head Pointer to the head of the `marena_t` doubly-linked-list.
// */
// marena_t    *marena_last(marena_t *head)
// {
//     if (!head)
//         return NULL;

//     while (head->next)
//         head = head->next;

//     return head;
// }

// void    marena_add_front(marena_t **head, marena_t *new)
// {
//     if (!new || !head)
//         return;

//     if (*head)
//         new->next = *head;
//     *head = new;
// }

// void    marena_add_back(marena_t **head, marena_t *new)
// {
//     marena_t    *last;

//     if (!new || !head)
//         return;

//     if (!*head)
//     {
//         *head = new;
//         return;
//     }

//     last = marena_last(*head);
//     last->next = new;
//     new->prev = last;
// }