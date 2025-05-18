/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multithreading.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-18 22:26:17 by nplieger          #+#    #+#             */
/*   Updated: 2025-05-18 22:26:17 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

/* *************************************************************************** */
/* *                                 STATIC                                  * */
/* *************************************************************************** */

/* Utils */

/* Tests */



/* *************************************************************************** */
/* *                                 LINKED                                  * */
/* *************************************************************************** */

static void *routine(void *t)
{
    void    *ptr = malloc(42);
    please_show_alloc_mem();
    return NULL;
}

void    test_multithreading(int fd)
{
    pthread_t   threads[1] = { 0 };

    // put_colored(BG_BOLD_BLACK, "Testing:        realloc(void *ptr, size_t size)     ", true, fd);

    for (size_t i = 0; i < sizeof(threads) / sizeof(*threads); i++)
        if (pthread_create(&threads[i], NULL, routine, NULL) != 0)
            threads[i] = 0;
            
    for (size_t i = 0; i < sizeof(threads) / sizeof(*threads); i++)
        if (threads[i] != 0)
            pthread_join(threads[i], NULL);
}
