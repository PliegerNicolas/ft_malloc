/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_infer_subcategory_name.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:45:17 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:45:17 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infers `mbin_subcategory_t` name representation
 * given `mbin_size` in bytes.
*/
char  *get_mbin_subcategory_name(size_t mbin_size)
{
    if (mbin_size <= TINY_MBIN_SIZE)
        return "MBIN_TINY";
    else if (mbin_size <= SMALL_MBIN_SIZE)
        return "MBIN_SMALL";
    else
        return "MBIN_LARGE";
}
