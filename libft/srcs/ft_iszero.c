/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iszero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:30:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/08 21:33:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Returns 1 if given long double is zero (all exponent and mantissa zero).
*/
int	ft_iszero(long double number)
{
	t_ldouble_cast	ldouble_cast;

	ldouble_cast.f = number;
	if (ldouble_cast.s_parts.exponent == 0
		&& ldouble_cast.s_parts.mantissa == 0)
		return (1);
	return (0);
}
