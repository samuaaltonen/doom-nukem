/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 19:07:55 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/08 21:33:11 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns log10 of given double. In case when input number is 0, returns 0.
 * Example:
 * log10(number) = exponent <=> 10^exponent = number
 * i.e. 
 * log10(0.1) would be -1
 * log10(0) would be inf (returns 0)
 * log10(1) would be 0
 * log10(10) would be 1
 * log10(123456) would be 5.09... (returns int so 5)
*/
int	ft_log10(long double number)
{
	int	exponent;

	if (ft_iszero(number))
		return (0);
	exponent = 0;
	if (number > 1.L)
	{
		while (number > 1.L)
		{
			number = number / 10;
			exponent++;
		}
		return (exponent - 1);
	}
	while (number < 1.L)
	{
		number = number * 10;
		exponent--;
	}
	return (exponent);
}
