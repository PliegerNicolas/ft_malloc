/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_mchunks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 09:27:38 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 09:27:38 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

size_t  put_mchunk_allocated_bytes(mchunk_t *mchunk)
{
    void    *mchunk_data_start_ptr;
    void    *mchunk_data_end_ptr;

    mchunk_data_start_ptr = GET_MCHUNK_DATA_PTR(mchunk);
    mchunk_data_end_ptr = (unsigned char *)mchunk_data_start_ptr + mchunk->allocation_size;

    ft_putptr_fd(mchunk_data_start_ptr, STDOUT_FILENO);
    ft_putstr_fd(" - ", STDOUT_FILENO);
    ft_putptr_fd(mchunk_data_end_ptr, STDOUT_FILENO);

    ft_putstr_fd(" : ", STDOUT_FILENO);

    ft_putsize_t_base_fd(mchunk->allocation_size, "0123456789", 10, STDOUT_FILENO);
    ft_putendl_fd(" bytes", STDOUT_FILENO);

    return mchunk->allocation_size;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

size_t  show_alloc_mem_mchunks(mregion_t *mregion)
{
    mchunk_t        *current_mchunk;
    size_t          total_allocated_bytes;
    unsigned char   *end_of_mregion;

    if (!mregion)
        return 0;

    end_of_mregion = (unsigned char *)mregion + mregion->size;

    total_allocated_bytes = 0;
    current_mchunk = GET_MREGION_FIRST_MCHUNK(mregion);
    while ((unsigned char *)current_mchunk < end_of_mregion)
    {
        if (current_mchunk->state == USED)
            total_allocated_bytes += put_mchunk_allocated_bytes(current_mchunk);
        current_mchunk = GET_NEXT_MCHUNK(current_mchunk);
    }

    return total_allocated_bytes;
}
