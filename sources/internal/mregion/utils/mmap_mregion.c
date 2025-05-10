/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-02 08:16:10 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-02 08:16:10 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *mmap_mregion(size_t bytes)
{
    void            *ptr;
    struct rlimit   rlimit;

    if (bytes == 0)
        return STATUS_FAILURE;

    // getrlimit should almost never fail.
    if (getrlimit(RLIMIT_AS, &rlimit) == -1)
        return STATUS_FAILURE;

    // Exists for potential more precise error handling.
    if (rlimit.rlim_cur != RLIM_INFINITY && bytes > rlimit.rlim_cur)
        return STATUS_FAILURE;

    ptr = mmap(NULL, ALIGN_UP(bytes, PAGE_SIZE), (PROT_READ | PROT_WRITE), (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
    if (ptr == MAP_FAILED)
        return STATUS_FAILURE;

    return ptr;
}
