/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_marena_once.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-12 19:41:51 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-12 19:41:51 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

marena_t    *init_marena_once(marena_t *marena)
{
    if (!marena)
        return printerr("init_marena_once()", "Wrong parameters", NULL), STATUS_FAILURE;

    if (marena->initialized)
        return marena;

    if (init_marena(marena) == STATUS_FAILURE)
        return STATUS_FAILURE;

    return marena;
}
