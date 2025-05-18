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
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/* Utils */

static void *check_malloc(const char *title, size_t size, const char *expected_result, int fd)
{
    void    *ptr;
    char    buffer[2048] = { '\0' };

    ft_putstr_fd(BOLD_CYAN, fd);
    if (title)
        ft_putstr_fd(title, fd);
    else
    {
        ft_putstr_fd("malloc(", fd);
        ft_putsize_t_fd(size, fd);
        ft_putchar_fd(')', fd);
    }        
    ft_putchar_fd(':', fd);
    ft_putendl_fd(RESET, fd);

    ft_putstr_fd("🞄 expecting: ", fd);
    ft_putendl_fd(expected_result, fd);

    {
        int     pipefd[2];
        int     original_stderr;
        ssize_t read_bytes;

        if (pipe(pipefd) == -1)
            return NULL;

        original_stderr = dup(STDERR_FILENO); // Duplicate STDERR so it can be restored later.
        if (original_stderr == -1)
            return close(pipefd[0]), close(pipefd[1]), NULL;

        if (dup2(pipefd[1], STDERR_FILENO) == -1) // Transform STDERR to pipefd[1] (write part of the pipe).
            return close(pipefd[0]), close(pipefd[1]), close(original_stderr), NULL;
        close(pipefd[1]); // Close the original pipefd[1] as it has now taken the place of STDERR.

        ptr = malloc(size);

        if (dup2(original_stderr, STDERR_FILENO) == -1)  // restore STDERR.
            return close(pipefd[0]), close(original_stderr), NULL;
        read_bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
        close(pipefd[0]); // Close the read end of the pipe.

        buffer[read_bytes] = '\0';
        if (read_bytes > 0 && buffer[read_bytes - 1] == '\n')
            buffer[read_bytes - 1] = '\0';
    }

    ft_putstr_fd("🞄 got: ", fd);
    ft_putptr_fd(ptr, fd);
    if (ft_strlen(buffer) > 0)
    {
        ft_putstr_fd(" (", fd);
        ft_putstr_fd(buffer, fd);
        ft_putchar_fd(')', fd);
    }
    ft_putchar_fd('\n', fd);

    return ptr;
}

/* Tests */

static void test_malloc_edge_cases(int fd)
{
    void    *ptrs[4] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Edge cases:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {
        ptrs[0] = check_malloc("malloc(0)", 0, "0x...", fd);
        ptrs[1] = check_malloc("malloc(MAX_ALLOCATION_SIZE)", MAX_ALLOCATION_SIZE, "(nil) (** mmap_mregion(): Not enough memory (ENOMEM) **)", fd);
        ptrs[2] = check_malloc("malloc(MAX_ALLOCATION_SIZE + 1)", MAX_ALLOCATION_SIZE + 1, "(nil) (** has_allocation_size_aberrant_value(): max allocation size exceeded **)", fd);
        ptrs[3] = check_malloc("malloc(SIZE_MAX)", SIZE_MAX, "(nil) (** has_allocation_size_aberrant_value(): max allocation size exceeded **)", fd);
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

static void test_malloc_mchunk_boundaries(int fd)
{
    void    *ptrs[6] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Mchunk boundaries:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {
        ptrs[0] = check_malloc("malloc(0)", 0, "0x...", fd);
        ptrs[1] = check_malloc("malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE)", TINY_MCHUNK_MAX_ALLOCATION_SIZE, "0x...", fd);
    
        ptrs[2] = check_malloc("malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1)", TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1, "0x...", fd);
        ptrs[3] = check_malloc("malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE)", SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "0x...", fd);

        ptrs[4] = check_malloc("malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1)", SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1, "0x...", fd);
        ptrs[5] = check_malloc("malloc(MAX_ALLOCATION_SIZE)", MAX_ALLOCATION_SIZE, "(nil) (** mmap_mregion(): Not enough memory (ENOMEM) **)", fd);
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

static void test_malloc_max_mchunks_per_mregion(int fd)
{
    void    *tiny_ptrs[MCHUNKS_PER_BOUND_MREGION] = { NULL };
    void    *small_ptrs[MCHUNKS_PER_BOUND_MREGION] = { NULL };
    void    *large_ptrs[MCHUNKS_PER_UNBOUND_MREGION] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Max mchunks per mregion:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {

        put_colored(BOLD_CYAN, "MCHUNKS_PER_BOUND_MREGION * malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE):", true, fd);
        ft_putendl_fd("🞄 expecting: only one populated tiny `mregion_t` (cf. 'Final arena state').", fd);
        for (size_t i = 0; i < sizeof(tiny_ptrs) / sizeof(*tiny_ptrs); i++)
            tiny_ptrs[i] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);

        put_colored(BOLD_CYAN, "MCHUNKS_PER_BOUND_MREGION * malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE):", true, fd);
        ft_putendl_fd("🞄 expecting: only one populated small `mregion_t` (cf. 'Final arena state').", fd);
        for (size_t i = 0; i < sizeof(small_ptrs) / sizeof(*small_ptrs); i++)
            small_ptrs[i] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE);

        put_colored(BOLD_CYAN, "MCHUNKS_PER_UNBOUND_MREGION * malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1):", true, fd);
        ft_putendl_fd("🞄 expecting: only one populated large `mregion_t` (cf. 'Final arena state').", fd);
        for (size_t i = 0; i < sizeof(large_ptrs) / sizeof(*large_ptrs); i++)
            large_ptrs[i] = malloc(SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1);
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(tiny_ptrs) / sizeof(*tiny_ptrs); i++)
        free(tiny_ptrs[i]); // Assuming free works fine.
    for (size_t i = 0; i < sizeof(small_ptrs) / sizeof(*small_ptrs); i++)
        free(small_ptrs[i]); // Assuming free works fine.
    for (size_t i = 0; i < sizeof(large_ptrs) / sizeof(*large_ptrs); i++)
        free(large_ptrs[i]); // Assuming free works fine.
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_malloc(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:            malloc(size_t size)             ", true, fd);

    test_malloc_edge_cases(fd);
    test_malloc_mchunk_boundaries(fd);
    test_malloc_max_mchunks_per_mregion(fd);
}
