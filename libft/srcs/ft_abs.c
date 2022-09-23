/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:21:04 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/30 09:59:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Returns absolute value of an int.
*/
int	ft_abs(int number)
{
	if (number < 0)
		return (-number);
	return (number);
}

/*
 * Returns absolute value of a double.
*/
double	ft_abs_double(double number)
{
	if (number < 0)
		return (-number);
	return (number);
}

/*
 * Returns absolute value of a long double.
*/
long double	ft_abs_ldouble(long double number)
{
	if (number < 0)
		return (-number);
	return (number);
}
