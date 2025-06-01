/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_marena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 11:31:16 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 11:31:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static size_t   print_mchunk(mchunk_t *mchunk, bool endl, int fd)
{
    void    *mchunk_data_left_bound;
    void    *mchunk_data_right_bound;

    if (!mchunk)
        return 0;

    mchunk_data_left_bound = GET_MCHUNK_DATA_PTR(mchunk);
    mchunk_data_right_bound = (void *)((unsigned char *)mchunk_data_left_bound + mchunk->allocation_size);

    ft_putptr_fd(mchunk_data_left_bound, fd);
    ft_putstr_fd(" - ", fd);
    ft_putptr_fd(mchunk_data_right_bound, fd);

    ft_putstr_fd(" : ", fd);

    ft_putsize_t_fd(mchunk->allocation_size, fd);
    ft_putstr_fd(" bytes", fd);
    if (endl)
        ft_putchar_fd('\n', fd);

    return mchunk->allocation_size;
}

static void print_mregion_title(const char *mregion_type_name, mregion_t *mregion, int fd)
{
    if (!mregion_type_name)
        return;

    ft_putstr_fd(mregion_type_name, fd);
    ft_putstr_fd(": ", fd);
    if (mregion)
        ft_putptr_fd(mregion, fd);
    ft_putchar_fd('\n', fd);
}

static size_t   print_mregion_mchunks(const char *mregion_type_name, mregion_t *mregion, int fd, bool print_free)
{
    size_t          allocated_bytes;
    mchunk_t        *mchunk;
    unsigned char   *mregion_right_data_bound;

    if (!mregion_type_name || !mregion)
        return 0;

    print_mregion_title(mregion_type_name, mregion, fd);

    mregion_right_data_bound = (unsigned char *)mregion + mregion->size;

    mchunk = GET_MREGION_FIRST_MCHUNK(mregion);
    while ((unsigned char *)mchunk < mregion_right_data_bound)
    {
        if (mchunk->state == USED)
        {
            allocated_bytes += print_mchunk(mchunk, false, fd);
            ft_putendl_fd(" (USED)", fd);
        }
        else if (print_free && mchunk->state == FREE)
        {
            (void)print_mchunk(mchunk, false, fd);
            ft_putendl_fd(" (FREE)", fd);
        }

        mchunk = GET_NEXT_MCHUNK(mchunk);
    }

    return allocated_bytes;
}

static size_t   print_mregion(const char *mregion_type_name, mregion_t *mregion, int fd, bool print_free)
{
    size_t  allocated_bytes;

    if (!mregion_type_name || !mregion)
        return 0;

    allocated_bytes = 0;
    for(mregion_t *curr_mregion = mregion; curr_mregion; curr_mregion = curr_mregion->next)
        allocated_bytes += print_mregion_mchunks(mregion_type_name, curr_mregion, fd, print_free);

    return allocated_bytes;
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

size_t  print_marena(marena_t *marena, int fd, bool print_free)
{
    size_t  allocated_bytes;

    if (!marena)
        return 0;

    allocated_bytes = 0;
    for (bound_mregion_type_t type = 0; type < NUM_BOUND_MREGION_TYPES; type++)
        allocated_bytes += print_mregion(map_mregion_bound_type_to_name(type), marena->bound_mregions[type], fd, print_free);
    allocated_bytes += print_mregion("LARGE", marena->unbound_mregion, fd, print_free);

    return allocated_bytes;  
}