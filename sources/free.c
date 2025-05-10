/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:19 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:19 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    free(void *ptr)
{
    mregion_t   **mregion;
    mchunk_t    *mchunk;

    if (init_gmarena_once() == STATUS_FAILURE)
        return;

    if (!ptr)
        return;

    mchunk = GET_MCHUNK_PTR(ptr);
    if (mchunk_has_aberrant_values(mchunk) || mchunk->state != USED)
        return;

    if (free_mchunk(GET_MCHUNK_PTR(ptr)) == STATUS_FAILURE)
        return;
}
