/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_infer_category.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:38:23 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:38:23 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer a `mbin_category_t` based on a `mbin_subcategory_t`.
*/
mbin_category_t  mbin_infer_category(mbin_subcategory_t subcategory)
{
    if (subcategory < MBIN_LARGE)
        return MBIN_UNIFORM;
    return MBIN_NON_UNIFORM;
}
