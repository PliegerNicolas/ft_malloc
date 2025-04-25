/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mregions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 22:58:43 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 22:58:43 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Initializes and/or adds a `total` amount of `mregion_t` nodes.
 * @param marena Pointer to the `mregion_t` to initialize. `NULL` causes failure.
 * @param mregion_size Minimal size of the `mregion_t` in bytes.
 * @param total Total `mregion_t`s to initialize, considering the linked-list structure.
 * 
 * @note `mregion_t`s are prepended.
 * Requested size is systematically rounded up to the next multiple of `PAGE_SIZE`.
 * 
 * @returns Operation related `status_t`.
 * 
 * On `STATUS_SUCCESS` the `mregion_t` is populated with one free `mchunk_t` in it's `mbin`.
 * If `mregion_size` is `0`, it's set to NULL.
 * On `STATUS_FAILURE` `mregion_t` is preserved as it was.
*/
status_t    init_mregions(mregion_t **mregion, size_t mregion_size,  size_t total)
{
    mregion_t   *new_mregion;

    if (!mregion)
        return STATUS_FAILURE;

    for (size_t i = 0; i < total; i++)
    {
        new_mregion = NULL;
        if (init_mregion(&new_mregion, mregion_size) == STATUS_FAILURE)
            return STATUS_FAILURE;
        prepend_mregion(mregion, new_mregion);
    }

    return STATUS_SUCCESS;
}
