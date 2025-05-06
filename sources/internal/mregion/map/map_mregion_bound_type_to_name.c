/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mregion_bound_category_to_name.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-06 17:01:00 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-06 17:01:00 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

const char  *map_mregion_bound_type_to_name(bound_mregion_type_t mregion_type)
{
    switch (mregion_type)
    {
        case TINY_MREGION_TYPE:
            return "TINY";
        case SMALL_MREGION_TYPE:
            return "SMALL";
        default: 
            return "UNDEFINED";
    }
}
