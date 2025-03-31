/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_heap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-30 18:06:19 by nicolas           #+#    #+#             */
/*   Updated: 2025-03-30 18:06:19 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// static mchunk_t *new_mchunk(size_t mmap_size)
// {
//     mchunk_t    *mchunk_ptr;
//     void        *mmap_ptr;

//     mmap_ptr = mmap(NULL, mmap_size, MMAP_PROTECTIONS, MMAP_FLAGS, -1, 0);
//     if (mmap_ptr == MAP_FAILED)
//         return MALLOC_FAILED;

//     mchunk_ptr = mmap_ptr;
//     *mchunk_ptr = (mchunk_t){
//         .state = FREE,
//         .size = mmap_size,
//         .prev_size = 0,
//         .next_free_chunk = NULL,
//         .prev_free_chunk = NULL,
//     };

//     return mchunk_ptr;
// }

// static size_t   get_mbin_size_by_category(enum e_mbin_category category, size_t fallback_size)
// {
//     switch(category)
//     {
//         case MBIN_TINY:
//             return TINY_MBIN_SIZE;
//         case MBIN_SMALL:
//             return SMALL_MBIN_SIZE;
//         case MBIN_LARGE:
//             return ALIGN_UP(fallback_size, PAGE_SIZE);
//         default:
//             return 0;
//     };
// }

// static mbin_t   new_mbin_by_size(size_t mbin_size)
// {
//     mbin_t      mbin = {0};
//     mchunk_t    *mchunk_ptr;
    
//     mchunk_ptr = new_mchunk(mbin_size);
//     if (mchunk_ptr == MALLOC_FAILED)
//         return mbin;

//     mbin.initial_chunk = mchunk_ptr;
//     mbin.size = mbin_size;

//     return mbin;
// }

// static marena_t new_arena()
// {
//     marena_t    arena = {0};

//     for (enum e_mbin_category c; c < NUM_MBIN_CATEGORIES; c++)
//         arena.bins[c] = new_mbin_by_size(get_mbin_size_by_category(c, 0));
//         // VALIDATION

//     return arena;
// }

// /**
//  * @brief Initializes a `heap_t` structure.
//  * 
//  * @param heap A pointer to the `heap_t` structure to be initialized.
//  * 
//  * @note It assumes that the `heap_t` structure already has valid memory space
//  * and has been zeroed out (e.g. global variable, static variable...).
// */
// void    initialize_heap(heap_t *heap)
// {
//     heap->arenas = new_arena();
//     heap->is_initialized = true;
// }
