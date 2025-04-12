/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 18:23:39 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 18:23:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/**
 * @brief Infer the size of a `mbin_t`
 * based on the amount of bytes we request to store in a `mchunk_t`.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
 * @note 
*/
size_t  get_mbin_size(size_t requested_bytes)
{
    if (requested_bytes <= TINY_MCHUNK_DATA_SIZE)
        return TINY_MBIN_SIZE;
    if (requested_bytes <= SMALL_MCHUNK_DATA_SIZE)
        return SMALL_MBIN_SIZE;
    return LARGE_MBIN_SIZE(requested_bytes);
}

/* ************************************************************************** */
/*                                 CATEGORIES                                 */
/* ************************************************************************** */

/** @brief Infer a `mbin_category_t` based on a `mbin_subcategory_t`. */
mbin_category_t  get_mbin_category(mbin_subcategory_t subcategory)
{
    return (subcategory < MBIN_LARGE) ? MBIN_UNIFORM : MBIN_NON_UNIFORM;
}

/**
 * @brief Infer a `mbin_subcategory_t` based on size of storable data in `mchunk_t`.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
mbin_subcategory_t  get_mbin_subcategory(size_t requested_bytes)
{
    if (requested_bytes < TINY_MCHUNK_DATA_SIZE)
        return MBIN_TINY;
    else if (requested_bytes < SMALL_MCHUNK_DATA_SIZE)
        return MBIN_SMALL;
    else
        return MBIN_LARGE;
};

/** 
 * @brief Infer a `MCHUNK_SIZE` based on a given `mbin_subcategory_t` and/or size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t  get_mbin_subcategory_mchunk_size(mbin_subcategory_t subcategory, size_t requested_bytes)
{
    switch(subcategory)
    {
        case MBIN_TINY:
            return TINY_MCHUNK_SIZE;
        case MBIN_SMALL:
            return SMALL_MCHUNK_SIZE;
        case MBIN_LARGE:
            return LARGE_MCHUNK_SIZE(requested_bytes);
        default:
            return 0;
    };
}

/**
 * @brief Infer a `MCHUNK_DATA_SIZE` based on a given `mbin_subcategory_t` and/or size in bytes.
 * @param requested_bytes The amount of bytes we want the `mchunk_t` to hold.
*/
size_t get_mbin_subcategory_mchunk_data_size(mbin_subcategory_t subcategory, size_t requested_bytes)
{
    switch(subcategory)
    {
        case MBIN_TINY:
            return TINY_MCHUNK_DATA_SIZE;
        case MBIN_SMALL:
            return SMALL_MCHUNK_DATA_SIZE;
        case MBIN_LARGE:
            return LARGE_MCHUNK_DATA_SIZE(requested_bytes);
        default:
            return 0;
    };
}

/* ************************************************************************** */
/*                               CATEGORY NAMES                               */
/* ************************************************************************** */

char *get_mbin_category_name(size_t mbin_size)
{
    return (mbin_size <= SMALL_MBIN_SIZE) ? "MBIN_UNIFORM" : "MBIN_NON_UNIFORM";
};

char *get_mbin_subcategory_name(size_t mbin_size)
{
    if (mbin_size <= TINY_MBIN_SIZE)
        return "MBIN_TINY";
    else if (mbin_size <= SMALL_MBIN_SIZE)
        return "MBIN_SMALL";
    else
        return "MBIN_LARGE";
};

