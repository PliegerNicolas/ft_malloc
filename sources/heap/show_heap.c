/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_heap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 23:19:14 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 23:19:14 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
void    show_heap(heap_t *heap, int fd)
{
    size_t  total_size;

    if (!heap->is_initialized)
        return;

    total_size = show_marena(&heap->marena, fd);

    ft_putstr_fd("Total: ", fd);
    ft_putsize_t_base_fd(total_size, "0123456789", 10, fd);
    ft_putendl_fd(" bytes", fd);
}