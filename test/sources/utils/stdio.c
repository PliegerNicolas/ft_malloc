/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-21 21:04:28 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-21 21:04:28 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

void    *readFromFdRoutine(void *arg)
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
