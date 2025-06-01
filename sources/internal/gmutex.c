/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gmutex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-18 21:58:51 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-18 21:58:51 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/** @brief Global mutex instance. */
pthread_mutex_t gmutex = PTHREAD_MUTEX_INITIALIZER;

status_t    gmutex_lock()
{
    return STATUS_FAILURE;
    if (pthread_mutex_lock(&gmutex) != 0)
        return STATUS_FAILURE;
    return STATUS_SUCCESS;
}

status_t    gmutex_unlock()
{
    if (pthread_mutex_unlock(&gmutex) != 0)
        return STATUS_FAILURE;
    return STATUS_SUCCESS;
}