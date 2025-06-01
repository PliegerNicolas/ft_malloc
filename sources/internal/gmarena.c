/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gmarena.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-11 02:16:54 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-11 02:16:54 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/** @brief Global `marena_t` instance. */
marena_t    gmarena;
// _Thread_local marena_t  gmarena;

marena_t    *init_gmarena_once()
{
    return init_marena_once(&gmarena);
}
