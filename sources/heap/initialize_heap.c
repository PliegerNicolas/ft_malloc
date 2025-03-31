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

static size_t   get_mbin_size_per_uniform_subcategory(enum e_mbin_uniform_subcategory category)
{
    switch (category)
    {
        case MBIN_TINY:
            return TINY_MBIN_SIZE;
        case MBIN_SMALL:
            return SMALL_MBIN_SIZE;
        default:
            return 0;
    }
}

static mbin_t *create_mbins(enum e_mbin_categories category, size_t bins, size_t mbin_size)
{
    mbin_t *mbin = NULL;

    if (bins == 0)
        return NULL;

    for (size_t i = 0; i < bins; i++)
    {
        mbin_add_front(&mbin, new_mbin(mbin_size, category));
    }

    return mbin;
}

void    initialize_heap(heap_t *heap)
{
    for (enum e_mbin_uniform_subcategory c = 0; c < NUM_UNIFORM_MBIN_SUBCATEGORIES; c++)
        heap->marena.uniform_mbins[c] = create_mbins(UNIFORM, TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY, get_mbin_size_per_uniform_subcategory(c));

    for (enum e_mbin_irregular_subcategory c = 0; c < NUM_IRREGULAR_MBIN_SUBCATEGORIES; c++)
        heap->marena.irregular_mbins[c] = create_mbins(IRREGULAR, 0, 0);

    heap->marena.irregular_mbins;
    heap->is_initialized = true;
}