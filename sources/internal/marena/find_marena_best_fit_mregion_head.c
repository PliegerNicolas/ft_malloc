/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_marena_best_fit_mregion_head.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 16:13:50 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-25 16:13:50 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Finds the `marena_t`s best fitted `mregion_t` linked-list head given an amount of bytes to store.
 * @param marena Pointer to given `marena_t` to look inside of.
 * @param allocation_size Expected amount of bytes to store in requested `mregion_t`.
 * 
 * @note If no `mregion_t` fits, it is initialized/created on the fly.
 * 
 * @returns The head of a `mregion_t` linked-list best fitted to store `allocation_size` bytes of data.
 * Or `STATUS_FAILURE` if it fails.
*/
mregion_t   *find_marena_best_fit_mregion_head(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion_head;
    size_t      mregion_size;
    
    mregion_head = map_allocation_size_to_marena_mregion_head(marena, allocation_size);
    mregion_size = map_allocation_size_to_mregion_size(allocation_size);

    if (init_mregion(mregion_head, mregion_size) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return *mregion_head;
}
