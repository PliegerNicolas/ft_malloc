/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_fit_mregion_head.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-22 20:31:27 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-22 20:31:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   *find_best_fit_mregion_head(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion_head;
    size_t      mregion_size;
    
    mregion_head = map_allocation_size_to_mregion_head(marena, allocation_size);
    if (!mregion_head) // Can in practice never happen.
        return STATUS_FAILURE;

    mregion_size = map_allocation_size_to_mregion_size(allocation_size);
    if (!*mregion_head && init_mregion(mregion_head, mregion_size) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return *mregion_head;
}
