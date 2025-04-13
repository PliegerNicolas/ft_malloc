/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin_infer_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-14 20:42:52 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-14 20:42:52 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infers `mbin_category_t` name representation
 * given `mbin_size` in bytes.
*/
char  *get_mbin_category_name(size_t mbin_size)
{
    return (mbin_size <= SMALL_MBIN_SIZE) ? "MBIN_UNIFORM" : "MBIN_NON_UNIFORM";
}
