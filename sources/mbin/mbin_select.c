/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:36:32 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:36:32 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Get the first `mbin_t*` node given a `mbin_category_t` and `mbin_subcategory_t`.
 * @note The returned node can be set to NULL. It means the specific `mbin_t` is empty.
*/
mbin_t  **mbin_select(heap_t *heap, mbin_category_t category, mbin_subcategory_t subcategory)
{
    if (!heap->is_initialized)
        return NULL;

    switch(category)
    {
        case MBIN_UNIFORM:
            return &heap->marena.uniform_mbins[GET_UNIFORM_MBIN_INDEX(subcategory)];
        case MBIN_NON_UNIFORM:
            return &heap->marena.non_uniform_mbins[GET_NON_UNIFORM_MBIN_INDEX(subcategory)];
        default:
            return NULL;
    };
}
