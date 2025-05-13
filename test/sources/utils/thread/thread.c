/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 00:20:14 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 00:20:14 by nplieger         ###   ########.fr       */
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

void    set_thread_as_ready(thread_sync_t *thread_sync)
{
    pthread_mutex_lock(&thread_sync->ready_mutex);
    thread_sync->is_ready = true;
    pthread_cond_signal(&thread_sync->ready_cond);
    pthread_mutex_unlock(&thread_sync->ready_mutex);
}

/**
 * @brief Launched thread is awaited and singular. Race conditions are possible but unlikely.
 * 
 * We use threads to trigger a new thread local storage instance. This forces a brand new `marena_t` to be initialized.
 * 
 * @warning Passed function should call at least once `set_thread_as_ready(thread_sync_t *)`.
 */
void    run_in_thread(void *(*fn)(void *arg), void *arg)
{
    pthread_t   thread;
    thread_sync_t thread_sync = {
        .thread_arg = arg,
        .is_ready = false,
        .ready_cond = PTHREAD_COND_INITIALIZER,
        .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    create_thread(&thread, fn, &thread_sync);
    close_thread(thread);
}
