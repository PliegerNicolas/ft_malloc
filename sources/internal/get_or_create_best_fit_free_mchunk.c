/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_or_create_best_fit_free_mchunk.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 10:06:31 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-04 10:06:31 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

mchunk_t    **get_or_create_best_fit_free_mchunk(marena_t *marena, size_t allocation_size)
{
    mregion_t   **mregion_head;
    mchunk_t    **best_fit_free_mchunk;

    if (!marena)
        return STATUS_FAILURE;

    if ((mregion_head = get_or_create_marena_fit_mregion_head(marena, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    if ((best_fit_free_mchunk = get_or_create_mregion_best_fit_free_mchunk(mregion_head, allocation_size)) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return best_fit_free_mchunk;
}
