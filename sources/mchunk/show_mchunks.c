/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mchunks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 23:19:30 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 23:19:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static size_t   put_in_use_mchunk(mchunk_t *mchunk, int fd)
{
    void        *mchunk_data_start_ptr;
    void        *mchunk_data_end_ptr;

    if (mchunk->state != IN_USE)
        return 0;

    mchunk_data_start_ptr = GET_MCHUNK_DATA_PTR(mchunk);
    mchunk_data_end_ptr = (unsigned char *)mchunk_data_start_ptr + mchunk->requested_size;

    ft_putptr_fd(mchunk_data_start_ptr, fd);
    ft_putstr_fd(" - ", fd);
    ft_putptr_fd(mchunk_data_end_ptr, fd);
    ft_putstr_fd(" : ", fd);
    ft_putsize_t_base_fd(mchunk->requested_size, "0123456789", 10, fd);
    ft_putendl_fd(" bytes", fd);

    return mchunk->requested_size;
}

size_t  show_mchunks(mchunk_t **initial_mchunk, int fd)
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
        total_allocated_bytes += put_in_use_mchunk(current_mchunk, fd);
        current_mchunk = GET_NEXT_MCHUNK(current_mchunk);
    };

    return total_allocated_bytes;
}