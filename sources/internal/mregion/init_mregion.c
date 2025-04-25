/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mregion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-20 22:58:35 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-20 22:58:35 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Wrapper for `mmap()` dedicated to memory allocation for `mregion_t`s.
 * @param bytes Number of bytes to allocate via `mmap()`.
 * 
 * @note Requested size is systematically rounded up to the next multiple of `PAGE_SIZE`.
 * Returned pointer has `READ` and `WRITE` perms, and are `PRIVATE` and `ANONYMOUS`.
 * 
 * @return A pointer to the allocated memory page, or `STATUS_FAILURE` if it fails.
*/
static void *mmap_mregion(size_t bytes)
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

/**
 * @brief Initializes a given `mregion_t` node.
 * @param marena Pointer to the `mregion_t` to initialize. `NULL` causes failure.
 * @param mregion_size Minimal size of the `mregion_t` in bytes.
 * 
 * @note Requested size is systematically rounded up to the next multiple of `PAGE_SIZE`.
 * 
 * @returns Operation related `status_t`.
 * 
 * On `STATUS_SUCCESS` the `mregion_t` is populated with one free `mchunk_t` in it's `mbin`.
 * If `mregion_size` is `0`, it's set to NULL.
 * On `STATUS_FAILURE` `mregion_t` is preserved as it was.
*/
status_t    init_mregion(mregion_t **mregion, size_t mregion_size)
{
    mregion_t    *new_mregion;
    mchunk_t    *new_mbin;
    size_t      mregion_padded_size;
    size_t      mbin_padded_size;

    if (!mregion)
        return STATUS_FAILURE;
    if (mregion_size == 0)
        return (*mregion = NULL), STATUS_SUCCESS;
    
    mregion_padded_size = ALIGN_UP(mregion_size, PAGE_SIZE);
    mbin_padded_size = mregion_padded_size - MREGION_HEADER_PADDED_SIZE;

    new_mregion = mmap_mregion(mregion_padded_size);
    if (new_mregion == STATUS_FAILURE)
        return STATUS_FAILURE;
    new_mbin = GET_MREGION_MBIN_PTR(new_mregion);

    *new_mbin = (mchunk_t) {
        .prev_allocation_size = 0,
        .allocation_size = mbin_padded_size,
        .next_free_mchunk = NULL,
        .prev_free_mchunk = NULL,
    };

    *new_mregion = (mregion_t) {
        .size = mregion_padded_size,
        .mbin = new_mbin,
        .next = NULL,
    };
    *mregion = new_mregion;

    return STATUS_SUCCESS;
}
