/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 00:20:10 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 00:20:10 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STDERR                                  * */
/* *************************************************************************** */

void    *listenToSTDERR(void *arg)
{
    thread_sync_t   *thread_sync = arg;

    if (thread_sync->is_ready)
        return set_thread_as_ready(thread_sync), NULL;

    fd_listener_t   *listener = thread_sync->thread_arg;

    if (!listener)
        return set_thread_as_ready(thread_sync), NULL;
    else if (listener->fd < 0 || listener->timeout.tv_sec < 0 || listener->timeout.tv_usec < 0)
        return set_thread_as_ready(thread_sync), NULL;

    ft_memset(listener->buffer, 0, sizeof(listener->buffer));
    listener->length = 0;

    int             pipefd[2];
    int             prev_fd;
    fd_set          selectFdsSet;

    if (pipe(pipefd) == -1)
        return set_thread_as_ready(thread_sync), NULL;

    // Preserve prev FD for later restitution.
    if ((prev_fd = dup(listener->fd)) == -1)
    {
        close(pipefd[0]); close(pipefd[1]);
        return set_thread_as_ready(thread_sync), NULL;
    }

    // Map listener->fd to pipefd's write end.
    if ((dup2(pipefd[1], listener->fd)) == -1)
    {
        close(pipefd[0]); close(pipefd[1]); close(prev_fd);
        return set_thread_as_ready(thread_sync), NULL;
    }
    close(pipefd[1]);

    FD_ZERO(&selectFdsSet);
    FD_SET(pipefd[0], &selectFdsSet);

    set_thread_as_ready(thread_sync);

    int ret = select(pipefd[0] + 1, &selectFdsSet, NULL , NULL, &listener->timeout);

    if (ret > 0 && FD_ISSET(pipefd[0], &selectFdsSet))
    {
        ssize_t read_bytes = read(pipefd[0], listener->buffer, sizeof(listener->buffer) - 1);

        if (read_bytes > 0)
        {
            if (listener->buffer[read_bytes - 1] == '\n')
                read_bytes -= 1;
            listener->buffer[read_bytes] = '\0';
            listener->length = read_bytes;
        }
    }

    // restore listener->fd.
    if (dup2(prev_fd, listener->fd) == -1)
        return close(prev_fd), NULL;
    close(prev_fd);

    return NULL;
}

/* *************************************************************************** */
/* *                                 MALLOC                                  * */
/* *************************************************************************** */

void    *run_malloc_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    test_t          *test = thread_sync->thread_arg;
    int             fd = STDOUT_FILENO;
    void            *ptr;
    
    set_thread_as_ready(thread_sync);

    // Put test.
    ft_putstr_fd(BOLD_CYAN, fd);
    if (test->test)
        ft_putstr_fd(test->test, fd);
    else
    {
        ft_putstr_fd("malloc(", fd);
        ft_putsize_t_fd(test->bytes, fd);
        ft_putstr_fd(")", fd);
    }
    ft_putchar_fd(':', fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);

    put_expected_result(test->expec_res, fd);

    // Exec malloc and capture it's stderr.
    fd_listener_t   stderr_listener = {
        .fd = STDERR_FILENO,
        .timeout = {
            .tv_sec = test->expec_err ? 5 : 0,
            .tv_usec = 0
        },
    };
    
    {
        pthread_t   thread;
        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });
        ptr = malloc(test->bytes);
        close_thread(thread);
    }

    put_test_result(ptr, stderr_listener.buffer, fd);
    put_memory_state(fd);

    // Free allocated ptr.
    free(ptr);

    return NULL;
}

void    *run_malloc_tests(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    tests_t         *tests = thread_sync->thread_arg;
    void            *ptrs[tests->size];
    int             fd = STDOUT_FILENO;
    
    set_thread_as_ready(thread_sync);

    // Put test.
    if (tests->test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(tests->test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    put_expected_result(tests->expec_res, fd);

    ft_bzero(ptrs, sizeof(ptrs));
    for (size_t i = 0; i < tests->size; i++)
        ptrs[i] = malloc(tests->values[i].bytes);

    put_memory_state(fd);

    // Free everything up
    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]);

    return NULL;
}