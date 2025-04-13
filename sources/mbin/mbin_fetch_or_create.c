/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_fetch_or_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:07:30 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:07:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Fetches the first node in given `heap_t*` from an `mbin_t*`
 * matching the inferred category given `requested_bytes` size.
 * If it doesn't exist, it is created in given `heap_t*`.
 * 
 * @return A `mbin_t**` or `FAILURE` if it failed.
*/
mbin_t  **mbin_fetch_or_create(heap_t *heap, size_t requested_bytes)
{
    mbin_t              **mbin;
    mbin_category_t     mbin_category;
    mbin_subcategory_t  mbin_subcategory;

    mbin_subcategory =  mbin_infer_subcategory(requested_bytes);
    mbin_category = mbin_infer_category(mbin_subcategory);
    mbin =  mbin_select(heap, mbin_category, mbin_subcategory);

    if (!mbin)
        return FAILURE;
    
    if (*mbin == NULL)
    {
        *mbin = mbin_create(requested_bytes);
        if (!*mbin)
            return FAILURE;
    }

    return mbin;
}
