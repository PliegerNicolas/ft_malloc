/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbins_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 21:24:51 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 21:24:51 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Create multiple `mbin_t` nodes of a given `mbin_subcategory_t`
 * with default values.
 * @param num_mbins Number of nodes to create.
 * 
 * @return The first node of a `mbin_t*` doubly-linked-list.
 * NULL if `num_mbins` is 0.
*/
mbin_t  *mbins_create(mbin_subcategory_t mbin_subcategory, size_t num_mbins)
{
    mbin_t  *initial_mbin;
    mbin_t  *next_mbin;
    size_t  mchunk_data_size;

    if (num_mbins == 0)
        return NULL;

    mchunk_data_size = mchunk_infer_data_size_by_mbin_subcategory(mbin_subcategory, 0);

    initial_mbin = mbin_create(mchunk_data_size);
    if (initial_mbin == FAILURE)
        return FAILURE;
    
    for (size_t i = 0; i < num_mbins - 1; i++)
    {
        next_mbin = mbin_create(mchunk_data_size);
        if (next_mbin == FAILURE)
            return (mbin_clear(&initial_mbin), FAILURE);
        mbin_prepend(&initial_mbin,  next_mbin);
    }

    return initial_mbin;
}
