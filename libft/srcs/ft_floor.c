/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:39:42 by saaltone          #+#    #+#             */
/*   Updated: 2022/02/16 13:59:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * To prevent infinite recursion (ends with stack overflow) only does recursion
 * up to 16384 times.
*/
static long double	ft_floor_protected(long double number, int stack)
{
	long long	max_ull;

	max_ull = (long long) 1 << 62;
	if (number < (long double) max_ull || stack > 16384)
		return ((long double)(long long)number);
	return (ft_floor_protected(number / 2, stack + 1) * 2);
}

/*
 * Floors given long double.
*/
long double	ft_floor(long double number)
{
	return (ft_floor_protected(number, 0));
}
