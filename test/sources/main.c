/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nplieger <nplieger@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-27 21:28:35 by nplieger          #+#    #+#             */
/*   Updated: 2025-04-27 21:28:35 by nplieger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ft_malloc.h"

int main() {
    int fd = STDOUT_FILENO;

    test_macros(fd);

    test_malloc(fd);
    test_free(fd);
    test_realloc(fd);

    return 0;
}
