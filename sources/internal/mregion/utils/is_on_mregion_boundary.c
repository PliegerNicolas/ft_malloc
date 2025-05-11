/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_mregion_boundary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 18:42:09 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 18:42:09 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

bool    is_on_mregion_boundary(mregion_t *mregion, mchunk_t *mchunk)
{
    if (!mregion || !mchunk)
        return false;
    return (unsigned char *)mchunk == (unsigned char *)mregion + mregion->size;
}