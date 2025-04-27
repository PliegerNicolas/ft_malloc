/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_marena_best_fit_mregion_head.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 09:59:04 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-04 09:59:04 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mregion_t   **get_or_create_marena_fit_mregion_head(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion_head;

    if (!marena)
        return STATUS_FAILURE;

    mregion_head = map_allocation_size_to_marena_mregion_head(marena, allocation_size);
    if (mregion_head == NULL && init_mregion(mregion_head, allocation_size) == STATUS_FAILURE)
        return STATUS_FAILURE;
        
    return mregion_head;
}
