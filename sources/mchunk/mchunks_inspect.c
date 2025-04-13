/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mchunks_inspect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:11:23 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:11:23 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void put_mchunk_if_in_use(mchunk_t *mchunk, int fd)
{
    const char      *base = "0123456789";
    const size_t    base_size = 10;
    void            *mchunk_data_start_ptr;
    void            *mchunk_data_end_ptr;

    if (mchunk->state != IN_USE)
        return;

    mchunk_data_start_ptr = GET_MCHUNK_DATA_PTR(mchunk);
    mchunk_data_end_ptr = (unsigned char *)mchunk_data_start_ptr + mchunk->requested_size;

    ft_putptr_fd(mchunk_data_start_ptr, fd) + ft_putstr_fd(" - ", fd) + ft_putptr_fd(mchunk_data_end_ptr, fd);
    ft_putstr_fd(" : ", fd);
    ft_putsize_t_base_fd(mchunk->requested_size, base, base_size, fd) + ft_putendl_fd(" bytes", fd);
}

/**
 * @brief Displays a human-readable representation of the allocated memory zones
 * in the given `mchunk_t*` list on the specified file descriptor.
 *
 * @note Does nothing if the initial_mchunk is NULL.
*/
size_t  mchunks_inspect(mchunk_t **initial_mchunk, int fd)
{
    mchunk_t    *current_mchunk;
    size_t      total_allocated_bytes = 0;
    void        *start_mchunk_data_ptr;
    void        *end_mchunk_data_ptr;

    if (!initial_mchunk || !*initial_mchunk)
        return total_allocated_bytes;

    current_mchunk = *initial_mchunk;
    while (current_mchunk->size > 0)
    {
        if (current_mchunk->state == IN_USE)
        {
            put_mchunk_if_in_use(current_mchunk, fd);
            total_allocated_bytes += current_mchunk->requested_size;
        }
        current_mchunk = GET_NEXT_MCHUNK_PTR(current_mchunk);
    };

    return total_allocated_bytes;
}