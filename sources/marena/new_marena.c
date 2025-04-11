/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_marena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-10 14:52:01 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-10 14:52:01 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static status_t populate_uniform_mbins(mbin_t *mbins[], size_t total_mbins)
{
    size_t  mchunk_data_size;
    mbin_t  *mbin;

    for (mbin_uniform_subcategory_t category = 0; category < NUM_MBIN_UNIFORM_SUBCATEGORIES; category++)
    {
        mchunk_data_size = get_mchunk_data_size_per_mbin_uniform_subcategory(category);
        for (size_t i = 0; i < total_mbins; i++)
        {
            mbin = new_mbin(mchunk_data_size);
            if (mbin == FAILURE)
                return FAILURE;
            prepend_mbin(&mbins[category], mbin);
        };
    };

    return SUCCESS;
}

static status_t populate_non_uniform_mbins(mbin_t *mbins[], size_t total_mbins)
{
    for (mbin_non_uniform_subcategory_t category = 0; category < NUM_MBIN_NON_UNIFORM_SUBCATEGORIES; category++)
        mbins[category] = NULL;

    return SUCCESS;
}

marena_t    new_marena(status_t *status)
{
    marena_t    marena;
    mbin_t      *mbin;
    size_t      mchunk_data_size;

    ft_bzero(marena.uniform_mbins, sizeof(marena.uniform_mbins));
    ft_bzero(marena.non_uniform_mbins, sizeof(marena.non_uniform_mbins));

    *status = populate_uniform_mbins(marena.uniform_mbins, TARGET_INITIAL_UNIFORM_MBINS_PER_CATEGORY);
    if (*status == FAILURE)
        return marena;

    *status = populate_non_uniform_mbins(marena.non_uniform_mbins, 0);
    if (*status == FAILURE)
        return marena;

    return marena;
}