/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 11:39:11 by niduches          #+#    #+#             */
/*   Updated: 2019/10/08 17:48:52 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main(void)
    {
//    uint8_t *ptr1 = ft_malloc(42);
//    uint8_t *ptr2 = ft_malloc(84);
//    uint8_t *ptr3 = ft_malloc(3467);
    uint8_t *ptr4 = ft_malloc(9223372036854775807U);

//    (void) ptr1;
//    (void) ptr2;
//    (void) ptr3;
    (void) ptr4;

    (void) show_alloc_mem_ex();

    return (0);
    }
