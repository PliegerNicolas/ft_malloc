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
    // /!\ Might miss some words but I don't want to add more complexity just for capturing stderr.
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
    if (test->executed_test)
        ft_putstr_fd(test->executed_test, fd);
    else
    {
        ft_putstr_fd("malloc(", fd);
        ft_putsize_t_fd(test->bytes, fd);
        ft_putstr_fd(")", fd);
    }
    ft_putchar_fd(':', fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);

    put_expected_result(test->expected_res, fd);

    // Exec malloc and capture it's stderr.
    fd_listener_t   stderr_listener = {
        .fd = STDERR_FILENO,
        .timeout = { .tv_sec = test->expected_err ? 3 : 0, .tv_usec = 0 },
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

    // Put test result.
    put_test_result(ptr, stderr_listener.buffer, fd);

    // Put memory state.
    put_memory_state(NULL, fd);

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
    if (tests->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(tests->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put expected result.
    put_expected_result(tests->expected_res, fd);

    ft_bzero(ptrs, sizeof(ptrs));
    for (size_t i = 0; i < tests->size; i++)
        ptrs[i] = malloc(tests->values[i].bytes);

    put_memory_state(NULL, fd);

    // Free everything up
    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]);

    return NULL;
}

/* *************************************************************************** */
/* *                                 REALLOC                                 * */
/* *************************************************************************** */

void    *run_realloc_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    test_t          *test = thread_sync->thread_arg;
    int             fd = STDOUT_FILENO;
    void            *ptr = NULL;

    set_thread_as_ready(thread_sync);

    // Put test.
    ft_putstr_fd(BOLD_CYAN, fd);
    if (test->executed_test)
        ft_putstr_fd(test->executed_test, fd);
    else
    {
        ft_putstr_fd("realloc(", fd);
        ft_putptr_fd(NULL, fd);
        ft_putstr_fd(", ", fd);
        ft_putsize_t_fd(test->bytes, fd);
        ft_putchar_fd(')', fd);
    }
    ft_putchar_fd(':', fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);

    // Put Results.
    put_expected_result(test->expected_res, fd);

    fd_listener_t   stderr_listener = {
        .fd = STDERR_FILENO,
        .timeout = { .tv_sec = test->expected_err ? 3 : 0, .tv_usec = 0 },
    };

    {
        pthread_t   thread;

        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });

        ptr = realloc(NULL, test->bytes);

        close_thread(thread);
    }

    // Put memory state.
    put_memory_state(NULL, fd);

    // Free everything up
    free(ptr);

    return NULL;
}

void    *run_realloc_with_neighbor_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    tests_t         *tests = thread_sync->thread_arg;
    int             fd = STDOUT_FILENO;

    void            *ptrs[3] = { 0 };
    bool            expect_error = false;

    set_thread_as_ready(thread_sync);

    if (tests->size < 2 && tests->size > 3)
        return ft_putendl_fd("Expected exacly 2 or 3 tests/values", STDERR_FILENO), NULL;

    for (size_t i = 0; i < tests->size; i++)
        if (tests->values[i].expected_err)
            expect_error = tests->values[i].expected_err;

    if (tests->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(tests->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put Results.
    put_expected_result(tests->expected_res, fd);

    fd_listener_t   stderr_listener = {
        .fd = STDERR_FILENO,
        .timeout = { .tv_sec = expect_error ? 5 : 0, .tv_usec = 0 },
    };

    {
        pthread_t   thread;

        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });

        if (tests->size == 2)
        {
            ptrs[0] = malloc(tests->values[0].bytes);
            // Put memory state.
            put_memory_state("before realloc()", fd);
            ptrs[1] = realloc(ptrs[0], tests->values[1].bytes);
            put_memory_state("after realloc()", fd);
            ptrs[0] = NULL;
        }
        else if (tests->size == 3)
        {
            ptrs[0] = malloc(tests->values[0].bytes);
            ptrs[1] = malloc(tests->values[1].bytes);
            put_memory_state("before realloc()", fd);
            ptrs[2] = realloc(ptrs[0], tests->values[2].bytes);
            put_memory_state("after realloc()", fd);
            ptrs[0] = NULL;
        }

        close_thread(thread);
    }

    // Free everything up
    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]);

    return NULL;
}

void    *run_realloc_chained_tests(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    tests_t         *tests = thread_sync->thread_arg;
    test_t          current_test;
    int             fd = STDOUT_FILENO;
    void            *ptr = NULL;

    set_thread_as_ready(thread_sync);

    // We do not capture STDERR here.

    if (tests->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(tests->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    ft_putendl_fd("🞄 Operations: ", fd);

    for (size_t i = 0; i < tests->size; i++)
    {
        current_test = tests->values[i];
        ptr = realloc(ptr, current_test.bytes);
        ft_putstr_fd("- realloc(prev_ptr, ", fd);
        ft_putsize_t_fd(current_test.bytes, fd);
        ft_putendl_fd(")", fd);
    }

    // Put Results.
    put_expected_result(tests->expected_res, fd);

    // Put memory state.
    put_memory_state(NULL, fd);

    // Free everything up
    free(ptr);

    return NULL;
}

/* *************************************************************************** */
/* *                                  FREE                                   * */
/* *************************************************************************** */

void    *run_free_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    test_t          *test = thread_sync->thread_arg;
    fd_listener_t   stderr_listener = { 0 };
    int             fd = STDOUT_FILENO;
    void            *ptr = NULL;

    set_thread_as_ready(thread_sync);

    // Put executed test
    if (test->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(test->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put expected result.
    if (test->expected_res)
        put_expected_result(test->expected_res, fd);

    // Put memory state.
    put_memory_state("before free()", fd);    

    {
        pthread_t   thread;
        stderr_listener.fd = STDERR_FILENO;
        stderr_listener.timeout = (struct timeval) { .tv_sec = test->expected_err ? 3 : 0, .tv_usec = 0 };

        if (test->ptr)
            ptr = test->ptr;
        else
            ptr = malloc(test->bytes);

        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });

        free(ptr);

        close_thread(thread);
    }

    // Put memory state.
    put_memory_state("after free()", fd);

    // Put test result.
    if (test->expected_res)
    {
        ft_putstr_fd("🞄 Got: ", fd);
        if (*stderr_listener.buffer)
            ft_putstr_fd(stderr_listener.buffer, fd);
        else
            ft_putstr_fd("nothing", fd);
        ft_putchar_fd('\n', fd);
    }

    return NULL;
}

void    *run_double_free_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    test_t          *test = thread_sync->thread_arg;
    fd_listener_t   stderr_listener = { 0 };
    int             fd = STDOUT_FILENO;
    void            *ptr = NULL;

    set_thread_as_ready(thread_sync);

    // Put executed test
    if (test->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(test->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put expected result.
    if (test->expected_res)
        put_expected_result(test->expected_res, fd);

    // Put memory state.
    put_memory_state("before free()", fd);    

    {
        pthread_t   thread;
        stderr_listener.fd = STDERR_FILENO;
        stderr_listener.timeout = (struct timeval) { .tv_sec = test->expected_err ? 3 : 0, .tv_usec = 0 };

        ptr = malloc(test->bytes);

        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wuse-after-free"
        free(ptr);
        free(ptr);
        #pragma GCC diagnostic pop

        close_thread(thread);
    }

    // Put memory state.
    put_memory_state("after free()", fd);

    // Put test result.
    if (test->expected_res)
    {
        ft_putstr_fd("🞄 Got: ", fd);
        if (*stderr_listener.buffer)
            ft_putstr_fd(stderr_listener.buffer, fd);
        else
            ft_putstr_fd("nothing", fd);
        ft_putchar_fd('\n', fd);
    }

    return NULL;
}

void    *run_corrupted_free_test(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    test_t          *test = thread_sync->thread_arg;
    fd_listener_t   stderr_listener = { 0 };
    int             fd = STDOUT_FILENO;
    void            *ptr = NULL;
    unsigned char   cached_byte;

    set_thread_as_ready(thread_sync);

    // Put executed test
    if (test->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(test->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put expected result.
    if (test->expected_res)
        put_expected_result(test->expected_res, fd);

    // Put memory state.
    put_memory_state("before free()", fd);    

    {
        pthread_t   thread;

        stderr_listener.fd = STDERR_FILENO;
        stderr_listener.timeout = (struct timeval) { .tv_sec = test->expected_err ? 3 : 0, .tv_usec = 0 };

        ptr = malloc(test->bytes);

        create_thread(&thread, listenToSTDERR, &(thread_sync_t) {
            .thread_arg = &stderr_listener,
            .is_ready = false,
            .ready_cond = PTHREAD_COND_INITIALIZER,
            .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
        });

        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wuse-after-free"
        cached_byte = *((unsigned char *)ptr - MCHUNK_HEADER_SIZE);
        ft_memset((unsigned char *)ptr - MCHUNK_HEADER_SIZE, 'a', 1);
        free(ptr);
        ft_memset((unsigned char *)ptr - MCHUNK_HEADER_SIZE, cached_byte, 1);
        free(ptr);
        #pragma GCC diagnostic pop

        close_thread(thread);
    }

    // Put memory state.
    put_memory_state("after free()", fd);

    // Put test result.
    if (test->expected_res)
    {
        ft_putstr_fd("🞄 Got: ", fd);
        if (*stderr_listener.buffer)
            ft_putstr_fd(stderr_listener.buffer, fd);
        else
            ft_putstr_fd("nothing", fd);
        ft_putchar_fd('\n', fd);
    }
    
    return NULL;
}

void    *run_free_tests(void *arg)
{
    thread_sync_t   *thread_sync = arg;
    tests_t          *tests = thread_sync->thread_arg;
    int             fd = STDOUT_FILENO;
    void            *ptrs[tests->size];
    bool            indexes_to_free[tests->size];

    // We do not capture STDERR here.

    ft_memset(ptrs, 0, sizeof(ptrs));
    ft_memset(indexes_to_free, true, sizeof(indexes_to_free));

    set_thread_as_ready(thread_sync);

    // Put executed test
    if (tests->executed_test)
    {
        ft_putstr_fd(BOLD_CYAN, fd);
        ft_putstr_fd(tests->executed_test, fd);
        ft_putchar_fd(':', fd);
        ft_putstr_fd(RESET, fd);
        ft_putchar_fd('\n', fd);
    }

    // Put expected result.
    if (tests->expected_res)
        put_expected_result(tests->expected_res, fd);

    for (size_t i = 0; i < tests->size; i++)
    {
        ptrs[i] = malloc(tests->values[i].bytes);
        // If a ptr is passed it's just an indication that that generated ptr should get freed. Onooooo !
        if (tests->values[i].ptr)
            indexes_to_free[i] = false;
    }
    
    // Put memory state.
    put_memory_state("before free()", fd);

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
    {
        if (indexes_to_free[i] == true)
        {
            free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }
    
    // Put memory state.
    put_memory_state("after free()", fd);

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]);

    return NULL;
}
