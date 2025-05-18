/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-13 21:03:57 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-13 21:03:57 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/* Utils */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuse-after-free"
static void *check_realloc(const char *title, void *ptr, size_t size, const char *expected_result, int fd)
{
    void    *new_ptr;
    char    buffer[2048] = { '\0' };

    ft_putstr_fd(BOLD_CYAN, fd);
    if (title)
        ft_putstr_fd(title, fd);
    else
    {
        ft_putstr_fd("realloc(", fd);
        ft_putptr_fd(ptr, fd);
        ft_putstr_fd(", ", fd);
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

        new_ptr = realloc(ptr, size);

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
    ft_putstr_fd(" => ", fd);
    ft_putptr_fd(new_ptr, fd);
    if (ft_strlen(buffer) > 0)
    {
        ft_putstr_fd(" (", fd);
        ft_putstr_fd(buffer, fd);
        ft_putchar_fd(')', fd);
    }
    ft_putchar_fd('\n', fd);

    return new_ptr;
}
#pragma GCC diagnostic pop

/* Tests */

static void test_realloc_edge_cases(int fd)
{
    void    *ptrs[5] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Edge cases:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {
        ptrs[0] = check_realloc("realloc(NULL, 0)", NULL, 0, "(nil) => 0x...            [equivalent to malloc(0)]", fd);

        ptrs[1] = check_realloc("realloc(prev_ptr, 0)", ptrs[0], 0, "prev_ptr => (nil).", fd);
        ptrs[0] = check_free(NULL, ptrs[0], "** free(): double free or corruption: 0x... **", fd);

        ptrs[2] = check_realloc("realloc(NULL, MAX_ALLOCATION_SIZE)", NULL, MAX_ALLOCATION_SIZE, "(nil) (** mmap_mregion(): Not enough memory (ENOMEM) **)", fd);
        ptrs[3] = check_realloc("realloc(NULL, MAX_ALLOCATION_SIZE + 1)", NULL, MAX_ALLOCATION_SIZE + 1, "(nil) (** mmap_mregion(): Not enough memory (ENOMEM) **)", fd);
        ptrs[4] = check_realloc("realloc(NULL, SIZE_MAX)", NULL, SIZE_MAX, "(nil) (** has_allocation_size_aberrant_value(): max allocation size exceeded **)", fd);
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

static void test_realloc_boundary_growth(int fd)
{
    void    *ptrs[7] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Mchunk boundaries growth:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {
        /* Tiny */
        ptrs[0] = check_realloc("realloc(NULL, 0)", NULL, 0, "(nil) => new_addr", fd);
        ptrs[1] = check_realloc("realloc(prev_ptr, 42)", ptrs[0], 42, "prev_ptr => prev_ptr", fd);
        ptrs[0] = NULL;
        ptrs[2] = check_realloc("realloc(prev_ptr, 43)", ptrs[1], 43, "prev_ptr => prev_ptr", fd);
        ptrs[1] = NULL;

        /* Small */
        ptrs[3] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1)", ptrs[2], TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1, "prev_addr => new_addr", fd);
        ptrs[2] = NULL;
        ptrs[4] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE + 42)", ptrs[3], TINY_MCHUNK_MAX_ALLOCATION_SIZE + 42, "prev_addr => prev_addr", fd);
        ptrs[3] = NULL;

        /* Large */
        ptrs[5] = check_realloc("realloc(prev_ptr, SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1)", ptrs[4], SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1, "prev_addr => new_addr", fd);
        ptrs[4] = NULL;
        ptrs[6] = check_realloc("realloc(prev_ptr, SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1000)", ptrs[5], SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1000, "prev_addr => prev_addr", fd);
        ptrs[5] = NULL;
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

static void test_realloc_boundary_shrinkage(int fd)
{
    void    *ptrs[7] = { NULL };

    ft_putstr_fd(UNDERLINE, fd);
    put_colored(BOLD_CYAN, "Mchunk boundaries shrinkage:", true, fd);

    put_colored(DIM_CYAN, "Operations:", true, fd);
    {
        /* Large */
        ptrs[0] = check_realloc("realloc(prev_ptr, SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1000)", NULL, SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1000, "(nil) => new_addr", fd);
        ptrs[1] = check_realloc("realloc(prev_ptr, SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1)", ptrs[0], SMALL_MCHUNK_MAX_ALLOCATION_SIZE + 1, "prev_addr => prev_addr", fd);
        ptrs[0] = NULL;

        /* Small */
        ptrs[2] = check_realloc("realloc(prev_ptr, SMALL_MCHUNK_MAX_ALLOCATION_SIZE)", ptrs[1], SMALL_MCHUNK_MAX_ALLOCATION_SIZE, "prev_addr => new_addr", fd);
        ptrs[1] = NULL;
        ptrs[3] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1)", ptrs[2], TINY_MCHUNK_MAX_ALLOCATION_SIZE + 1, "prev_addr => prev_addr", fd);
        ptrs[2] = NULL;

        /* Tiny */
        ptrs[4] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE)", ptrs[3], TINY_MCHUNK_MAX_ALLOCATION_SIZE, "prev_addr => new_addr", fd);
        ptrs[3] = NULL;
        ptrs[5] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE)", ptrs[4], 1, "prev_addr => prev_addr", fd);
        ptrs[4] = NULL;
        ptrs[6] = check_realloc("realloc(prev_ptr, TINY_MCHUNK_MAX_ALLOCATION_SIZE)", ptrs[5], 0, "prev_addr => (nil)", fd);
        ptrs[5] = NULL;
    }

    put_colored(DIM_CYAN, "Final arena state:", true, fd);
    {
        please_show_alloc_mem();
    }

    for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
        free(ptrs[i]); // Assuming free works fine.
}

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_realloc(int fd)
{
    put_colored(BG_BOLD_BLACK, "Testing:        realloc(void *ptr, size_t size)     ", true, fd);

    test_realloc_edge_cases(fd);
    test_realloc_boundary_growth(fd);
    test_realloc_boundary_shrinkage(fd);
}
