/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mchunk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 13:31:12 by nicolas           #+#    #+#             */
/*   Updated: 2025-04-11 13:31:12 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

// static uniform_mchunk_t add_uniform_mchunk()
// {

// }

// void    mchunkify_uniform_mbin(mbin_t *uniform_mbin)
// {
//     if (uniform_mbin->category != MBIN_UNIFORM)
//         return; // Or other failure strategy.

//     uniform_mbin->uniform_start
// }

// /**
//  * @brief ...
// */
// uniform_mchunk_t new_uniform_mchunk(uniform_mchunk_t *prev)
// {
//     uniform_mchunk_t    uniform_mchunk;

//     uniform_mchunk.state = FREE;
//     uniform_mchunk.next_free_mchunk = NULL; // TODO: ???
//     uniform_mchunk.prev_free_mchunk = NULL; // TODO: ???

//     return uniform_mchunk;
// }

// /**
//  * @brief ...
// */
// nonuniform_mchunk_t new_nonuniform_mchunk(nonuniform_mchunk_t *prev)
// {
//     nonuniform_mchunk_t    nonuniform_mchunk;

//     nonuniform_mchunk.state = FREE;
//     nonuniform_mchunk.prev_size = prev->size;
//     nonuniform_mchunk.size = 0;
//     nonuniform_mchunk.next_free_mchunk = NULL; // TODO: ???
//     nonuniform_mchunk.prev_free_mchunk = NULL; // TODO: ???

//     return nonuniform_mchunk;
// }