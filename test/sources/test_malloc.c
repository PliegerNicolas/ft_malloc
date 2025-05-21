/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:03:47 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:03:47 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                              TEST EXECUTOR                              * */
/* *************************************************************************** */

static void print_check_malloc_title(size_t bytes, int fd)
{
    ft_putstr_fd(BOLD_CYAN, fd);
    ft_putstr_fd("malloc(", fd);
    ft_putsize_t_fd(bytes, fd);
    ft_putchar_fd(')', fd);
    ft_putchar_fd(':', fd);
    ft_putendl_fd(RESET, fd);
}

static void print_check_malloc_expecting(const char *expected_result, int fd)
{
    ft_putstr_fd("🞄 Expecting: ", fd);
    ft_putendl_fd(expected_result, fd);
}

static void *print_check_malloc_result(size_t bytes, size_t thread_timeout, int fd)
{
    pthread_t       thread;
    void            *ptr;

    fd_listener_t   stderr_listener = { 0 };
    thread_sync_t   thread_sync = {
        .thread_arg = &stderr_listener,
        .is_ready = false,
        .ready_cond = PTHREAD_COND_INITIALIZER,
        .ready_mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    stderr_listener.fd = STDERR_FILENO;
    stderr_listener.timeout.tv_sec = thread_timeout;
    stderr_listener.timeout.tv_usec = 0;

    if (!create_thread(&thread, readFromFdRoutine, &thread_sync))
        return NULL;
    ptr = malloc(bytes);
    close_thread(thread);

    ft_putstr_fd("🞄 Got: ", fd);
    ft_putptr_fd(ptr, fd);
    if (stderr_listener.buffer[0])
    {
        ft_putchar_fd(' ', fd);
        ft_putstr_fd(stderr_listener.buffer, fd);
    }
    ft_putchar_fd('\n', fd);

    return ptr;
}

static void print_check_malloc_memory_state(int fd)
{
    ft_putstr_fd(BOLD_CYAN, fd);
    ft_putstr_fd("Memory state: ", fd);
    ft_putstr_fd(RESET, fd);
    ft_putchar_fd('\n', fd);

    please_show_alloc_mem();
}

static void    check_malloc(size_t bytes, const char *expected_result, size_t thread_timeout, int fd)
{
    void    *ptr;

    print_check_malloc_title(bytes, fd);
    print_check_malloc_expecting(expected_result, fd);
    ptr = print_check_malloc_result(bytes, thread_timeout, fd);
    print_check_malloc_memory_state(fd);

    free(ptr);
}

/* *************************************************************************** */
/* *                              TESTS                                      * */
/* *************************************************************************** */

void    test_malloc(int fd)
{
    put_title("Testing:                               malloc(size_t size)                              ", (char*[]){ BG_BOLD_BLACK }, 1, fd);

    put_title("1. malloc(any)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(0, "0x...", 0, fd);
    check_malloc(1, "0x...", 0, fd);

    put_title("2. malloc(ALIGNMENT_BOUNDARY)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(ALIGNMENT_BOUNDARY - 1, "0x...", 0, fd);
    check_malloc(ALIGNMENT_BOUNDARY, "0x...", 0, fd);
    check_malloc(ALIGNMENT_BOUNDARY + 1, "0x...", 0, fd);

    put_title("2. malloc(MCHUNK_HEADER_SIZE)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(MCHUNK_HEADER_SIZE - 1, "0x...", 0, fd);
    check_malloc(MCHUNK_HEADER_SIZE, "0x...", 0, fd);
    check_malloc(MCHUNK_HEADER_SIZE + 1, "0x...", 0, fd);

    put_title("4. malloc(*_MCHUK_MAX_ALLOCATION_SIZE)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE / 2, "0x...", 0, fd);
    check_malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE, "0x...", 0, fd);
    check_malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1, "0x...", 0, fd);
    check_malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE / 2, "0x...", 0, fd);
    check_malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "0x...", 0, fd);
    check_malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1, "0x...", 0, fd);
    check_malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE * 2, "0x...", 0, fd);

    put_title("5. malloc(PAGE_SIZE)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(PAGE_SIZE - 1, "0x...", 0, fd);
    check_malloc(PAGE_SIZE, "0x...", 0, fd);
    check_malloc(PAGE_SIZE + 1, "0x...", 0, fd);

    put_title("6. malloc(MAX_ALLOCATION_SIZE)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(MAX_ALLOCATION_SIZE - 1, "(nil) ** mmap_mregion(): Not enough memory (ENOMEM) **", 5, fd);
    check_malloc(MAX_ALLOCATION_SIZE, "(nil) ** mmap_mregion(): Not enough memory (ENOMEM) **", 5, fd);
    check_malloc(MAX_ALLOCATION_SIZE + 1, "(nil) ** has_allocation_size_aberrant_value(): max allocation size exceeded **", 5, fd);

    put_title("7. malloc(MAX_ALLOCATION_SIZE)", (char*[]){ BG_BLACK, BRIGHT_BLUE }, 2, fd);
    check_malloc(SIZE_MAX - 1, "(nil) ** mmap_mregion(): Not enough memory (ENOMEM) **", 5, fd);
    check_malloc(SIZE_MAX, "(nil) ** has_allocation_size_aberrant_value(): max allocation size exceeded **", 5, fd);
    check_malloc(SIZE_MAX + 1, "0X...", 0, fd);
}
