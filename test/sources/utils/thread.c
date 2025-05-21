/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 20:58:05 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-21 20:58:05 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

static void wait_until_thread_ready(thread_sync_t *thread_sync)
{
    pthread_mutex_lock(&thread_sync->ready_mutex);

    while (!thread_sync->is_ready)
        pthread_cond_wait(&thread_sync->ready_cond, &thread_sync->ready_mutex);

    pthread_mutex_unlock(&thread_sync->ready_mutex);
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    set_thread_as_ready(thread_sync_t *thread_sync)
{
    pthread_mutex_lock(&thread_sync->ready_mutex);
    thread_sync->is_ready = true;
    pthread_cond_signal(&thread_sync->ready_cond);
    pthread_mutex_unlock(&thread_sync->ready_mutex);
}

bool    create_thread(pthread_t *thread, void *(*fn)(void *arg), thread_sync_t *thread_sync)
{
    if (!thread || !fn || !thread_sync || thread_sync->is_ready)
        return false;

    if (pthread_create(thread, NULL, fn, (void*)thread_sync) != 0)
        return false;

    return wait_until_thread_ready(thread_sync), true;
}

bool    close_thread(pthread_t thread)
{
    return pthread_join(thread, NULL) == 0;
}