/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_inspect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:07:48 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:07:48 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void put_mbin_category_and_ptr_address(mbin_t *mbin, int fd)
{
    char    *mbin_subcategory_name;
    void    *mbin_ptr;

    mbin_subcategory_name = get_mbin_subcategory_name(mbin->size);
    mbin_ptr = mbin;

    ft_putstr_fd(mbin_subcategory_name, fd) + ft_putstr_fd(": ", fd);
    ft_putptr_fd(mbin_ptr, fd) + ft_putchar_fd('\n', fd);
}

/**
 * @brief Displays a human-readable representation of the allocated memory zones
 * in the given `mbin_t **` on the specified file descriptor.
 *
 * @note Does nothing if the heap is NULL.
*/
size_t  mbin_inspect(mbin_t **mbin, int fd)
{
    mbin_t  *current_mbin;
    char    *mbin_subcategory;
    size_t  total_allocated_size;
    
    if (!mbin || !*mbin)
    return 0;
    
    current_mbin = *mbin;
    total_allocated_size = 0;

    while (current_mbin)
    {
        put_mbin_category_and_ptr_address(current_mbin, fd);
        total_allocated_size += mchunks_inspect(&current_mbin->start, fd);
        current_mbin = current_mbin->next;
    }

    return total_allocated_size;
}