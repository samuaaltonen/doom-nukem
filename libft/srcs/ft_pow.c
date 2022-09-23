/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:20:27 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/19 13:05:52 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double number, double power)
{
	double	i;
	double	result;

	if (power == 0)
		return (1);
	i = 0;
	result = number;
	while ((i < power - 1) || (power < 0 && i < (-power) - 1))
	{
		result = result * number;
		i++;
	}
	if (power < 0)
		result = 1 / result;
	return (result);
}
