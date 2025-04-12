/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mbin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 23:19:21 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-12 23:19:21 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief ...
*/
size_t  show_mbin(mbin_t **mbin, int fd)
{
    mbin_t  *current_mbin;
    char    *mbin_subcategory;
    size_t  total_allocated_size = 0;
    
    if (!mbin || !*mbin)
        return total_allocated_size;

    current_mbin = *mbin;
    while (current_mbin)
    {
        mbin_subcategory = get_mbin_subcategory_name(current_mbin->size);

        ft_putstr_fd(mbin_subcategory, fd);
        ft_putstr_fd(": ", fd);
        ft_putptr_fd(current_mbin, fd);
        ft_putchar_fd('\n', fd);

        total_allocated_size += show_mchunks(&current_mbin->start, fd);
        
        current_mbin = current_mbin->next;
    };

    return total_allocated_size;
}