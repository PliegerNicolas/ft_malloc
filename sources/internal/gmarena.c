/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gmarena.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-01 20:08:20 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-01 20:08:20 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/** @brief Global `marena_t` instance. */
marena_t    gmarena;

status_t    init_gmarena_once()
{
    return init_marena_once(&gmarena);
}