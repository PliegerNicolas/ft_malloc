/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_inspect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:06:22 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:06:22 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void put_total_allocated_bytes(size_t total_bytes, int fd)
{
    const char      *base = "0123456789";
    const size_t    base_size = 10;

    ft_putstr_fd("Total: ", fd);
    ft_putsize_t_base_fd(total_bytes, base, base_size, fd);
    ft_putendl_fd(" bytes.", fd);
}

/**
 * @brief Displays a human-readable representation of the allocated memory zones
 * in the given `heap_t*` on the specified file descriptor.
 *
 * @note Does nothing if the heap is uninitialized.
*/
size_t  heap_inspect(heap_t *heap, int fd)
{
    size_t  total_size;

    if (!heap->is_initialized)
        return 0;

    total_size = marena_inspect(&heap->marena, fd);
    put_total_allocated_bytes(total_size, fd);

    return total_size;
}
