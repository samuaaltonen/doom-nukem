/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftdiv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 22:01:05 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:04:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Converts exponential form of float to division of 2 integers. 
 * Example (single precision but same method for double and extended):
 * 
 * 1.75f = 00111111111000000000000000000000
 * [sign = 0][exponent = 01111111 = 127][mantissa = 11000000000000000000000]
 * Exponent is biased by 127 (offset), so substracting 127 leaves 0 as exponent
 * Mantissa is 6291456
 * 
 * Equation is: (1 + [mantissa] / 2^23) * 2^([exponent]-127)
 *            = (1 + 6291456 / 2^23) * 2^0
 *            = 1 + 6291456 / 8388608 = 1.75
 * 
 * The idea is to modify this equation so that it becomes a fraction of two
 * integers instead of exponential form:
 * 
 * (1 + [mantissa] / 2^23) * 2^([exponent]-127) * 2^0
 * (1 + [mantissa] / 2^23) * 2^([exponent]-127) * 2^(23-23)
 * (1 + [mantissa] / 2^23) * 2^([exponent]-127-23) * 2^23
 * (2^23 + [mantissa]) * 2^([exponent]-127-23)
 * (2^23 + [mantissa]) / 2^-([exponent]-127-23)
 * numerator           / denumerator
 * 
 * Using same numbers as above:
 * 1.75f = (2^23 + 6291456) / 2^-(127-127-23) = 14680064 / 8388608 = 1.75
 * 
 * single precision (float) exponent is biased by 127
 * double precision (double) exponent is biased by 1023
 * extended precision (long double) exponent is biased by 16383
*/
int	ft_ftdiv(long double number, t_superint **n, t_superint **d)
{
	t_sll			denum_exp;
	t_ldouble_cast	ldouble_cast;

	ldouble_cast.f = number;
	*n = ft_superint_new(((t_ull) 1) << 63, 3);
	*d = ft_superint_new(1, 3);
	if (!(*n) || !(*d)
		|| !ft_superint_plus_ull(n, ldouble_cast.s_parts.mantissa))
		return (0);
	denum_exp = ldouble_cast.s_parts.exponent - 16446;
	if (denum_exp > 0)
	{
		if (!ft_superint_shift(n, denum_exp))
			return (0);
	}
	else if (!ft_superint_shift(d, -denum_exp))
		return (0);
	return (1);
}

/*
 * Scales given numerator and denumerator by adding zeros so that the result
 * of division casted to int is allways one digit.
 * If log10 is higher than 0 it means that the original number is 10 or
 * higher, therefore we need to scale denumerator up.
 * Similarly, if log10 is less than 0, we scale numerator up.
 * Only scales up and not down to avoid losing any precision.
*/
int	ft_ftdiv_scale(int log10, t_superint **n, t_superint **d)
{
	if (log10 < 0)
	{
		while (log10 < 0)
		{
			if (!ft_superint_multiply_int(n, 10))
				return (0);
			log10++;
		}
		return (1);
	}
	while (log10 > 0)
	{
		if (!ft_superint_multiply_int(d, 10))
			return (0);
		log10--;
	}
	return (1);
}

/*
 * Log10 might be wrong (could be overshot because it is calculated with
 * float arithmetics). Check if first int of quotient is 0 (overshot) and 
 * reduce log10 if necessary.
*/
int	ft_ftdiv_logcheck(int *log10, t_superint **n, t_superint **d)
{
	t_superint	*mod;
	t_ull		result;

	if (ft_superint_iszero(n))
		return (1);
	mod = ft_superint_new(0, 3);
	if (!mod)
		return (0);
	if (ft_superint_divide_samesize(n, d, &mod, &result) <= 0)
		return (0);
	if (result == 0)
	{
		if (!ft_superint_multiply_int(n, 10))
			return (0);
		(*log10)--;
	}
	ft_superint_destroy(&mod);
	return (1);
}
