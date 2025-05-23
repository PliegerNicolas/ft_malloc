/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 17:49:16 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-22 17:49:16 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

void    test_free(int fd)
{
    put_title("Testing:                                free(void *ptr)                                 ", BG_BOLD_BLACK, fd);
    
    // Single free calls

    // Bulk free calls
}


// /* *************************************************************************** */
// /* *                                 STATIC                                  * */
// /* *************************************************************************** */

// /* Utils */

// void    *check_free(const char *title, void *ptr, const char *expected_result, int fd)
// {
//     char    buffer[2048] = { '\0' };

//     ft_putstr_fd(BOLD_CYAN, fd);
//     if (title)
//         ft_putstr_fd(title, fd);
//     else
//     {
//         ft_putstr_fd("free(", fd);
//         ft_putptr_fd(ptr, fd);
//         ft_putchar_fd(')', fd);
//     }
//     ft_putchar_fd(':', fd);
//     ft_putendl_fd(RESET, fd);

//     if (expected_result)
//     {
//         ft_putstr_fd("🞄 expecting: ", fd);
//         ft_putendl_fd(expected_result, fd);
//     }

//     {
//         int     pipefd[2];
//         int     original_stderr;
//         ssize_t read_bytes;

//         if (pipe(pipefd) == -1)
//             return NULL;

//         original_stderr = dup(STDERR_FILENO); // Duplicate STDERR so it can be restored later.
//         if (original_stderr == -1)
//             return close(pipefd[0]), close(pipefd[1]), NULL;

//         if (dup2(pipefd[1], STDERR_FILENO) == -1) // Transform STDERR to pipefd[1] (write part of the pipe).
//             return close(pipefd[0]), close(pipefd[1]), close(original_stderr), NULL;
//         close(pipefd[1]); // Close the original pipefd[1] as it has now taken the place of STDERR.

//         free(ptr);

//         if (dup2(original_stderr, STDERR_FILENO) == -1)  // restore STDERR.
//             return close(pipefd[0]), (void)close(original_stderr), NULL;
//         read_bytes = read(pipefd[0], buffer, sizeof(buffer) - 1);
//         close(pipefd[0]); // Close the read end of the pipe.

//         buffer[read_bytes] = '\0';
//         if (read_bytes > 0 && buffer[read_bytes - 1] == '\n')
//             buffer[read_bytes - 1] = '\0';
//     }

//     if (expected_result)
//     {
//         ft_putstr_fd("🞄 got: ", fd);
//         if (ft_strlen(buffer) > 0)
//             ft_putstr_fd(buffer, fd);
//         ft_putchar_fd('\n', fd);
//     }

//     return NULL;
// }

// /* Tests */

// static void test_double_free(int fd)
// {
//     void    *ptrs[2] = { NULL };

//     ft_putstr_fd(UNDERLINE, fd);
//     put_colored(BOLD_CYAN, "Edge cases:", true, fd);

//     put_colored(DIM_CYAN, "Operations:", true, fd);
//     {
//         ptrs[0] = malloc(42);
//         ptrs[1] = ptrs[0];

//         ptrs[0] = check_free(NULL, ptrs[0], "", fd);
//         ptrs[1] = check_free(NULL, ptrs[1], "** free(): double free or corruption: 0x... **", fd);
//     }

//     put_colored(DIM_CYAN, "Final arena state:", true, fd);
//     {
//         please_show_alloc_mem();
//     }

//     for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         free(ptrs[i]); // Assuming free works fine.
// }

// static void test_free_on_corrupted_mchunk(int fd)
// {
//     void    *ptrs[2] = { NULL };

//     ft_putstr_fd(UNDERLINE, fd);
//     put_colored(BOLD_CYAN, "Edge cases:", true, fd);

//     put_colored(DIM_CYAN, "Operations:", true, fd);
//     {
//         size_t          aligned_size = ALIGNMENT_BOUNDARY;
//         unsigned char   *cache[MCHUNK_HEADER_SIZE];

//         ptrs[0] = malloc(aligned_size);
//         ptrs[1] = malloc(aligned_size);

//         // Cache mchunk metadata before corruption.
//         ft_memcpy(cache, GET_MCHUNK_PTR(ptrs[1]), sizeof(cache));

//         ft_memset(ptrs[0] + aligned_size, 'a', 1);
//         check_free(NULL, ptrs[1], "** has_mchunk_aberrant_values(): corrupted mchunk: 0x... **", fd);

//         // Restore mchunk after corruption.
//         ft_memcpy(GET_MCHUNK_PTR(ptrs[1]), cache, sizeof(cache));
//     }

//     put_colored(DIM_CYAN, "Final arena state:", true, fd);
//     {
//         please_show_alloc_mem();
//     }

//     for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         free(ptrs[i]); // Assuming free works fine.
// }

// static void test_coalesce_on_free(int fd)
// {
//     void    *ptrs[MCHUNKS_PER_BOUND_MREGION] = { NULL };

//     ft_putstr_fd(UNDERLINE, fd);
//     put_colored(BOLD_CYAN, "Edge cases:", true, fd);

//     put_colored(DIM_CYAN, "Operations:", true, fd);
//     {
//         for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//             ptrs[i] = malloc(TINY_MCHUNK_MAX_ALLOCATION_SIZE);

//         put_colored(BOLD_CYAN, "Free() every free triplets in a list:", true, fd);
//         ft_putendl_fd("🞄 expecting: isolated free mchunks of regular sizes except potentially the last one (cf. 'Final arena state').", fd);

//         for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         {
//             if (i % 2 != 0)
//                 continue;
//             free(ptrs[i]);
//             ptrs[i] = NULL;
//         }

//         for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         {
//             if (i % 4 != 1)
//                 continue;
//             free(ptrs[i]);
//             ptrs[i] = NULL;
//         }
//     }

//     put_colored(DIM_CYAN, "Final arena state:", true, fd);
//     {
//         please_show_alloc_mem();
//     }

//     for (size_t i = 0; i < sizeof(ptrs) / sizeof(*ptrs); i++)
//         free(ptrs[i]); // Assuming free works fine.
// }

// /* *************************************************************************** */
// /* *                                 LINKED                                  * */
// /* *************************************************************************** */

// void    test_free(int fd)
// {
//     put_colored(BG_BOLD_BLACK, "Testing:            free(void *ptr)                 ", true, fd);

//     test_double_free(fd);
//     test_free_on_corrupted_mchunk(fd);
//     test_coalesce_on_free(fd);
// }