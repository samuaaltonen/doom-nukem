/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:59:36 by saaltone          #+#    #+#             */
/*   Updated: 2022/02/16 15:27:40 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(long long number)
{
	int	digits;

	digits = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number = number / 10;
		digits++;
	}
	return (digits);
}

int	ft_count_digits_ull(unsigned long long number)
{
	int	digits;

	digits = 0;
	if (number == 0)
		return (1);
	while (number != 0)
	{
		number = number / 10;
		digits++;
	}
	return (digits);
}

int	ft_count_digits_ld(long double number)
{
	int	digits;

	digits = 0;
	if (number == 0)
		return (1);
	while (number > 0.5)
	{
		number /= 10;
		digits++;
	}
	return (digits);
}
