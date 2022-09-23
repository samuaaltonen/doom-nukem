/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:56:17 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 13:42:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\f');
}

static int	is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

static int	handle_long_overflow(unsigned long number, int is_negative)
{
	if (number > 9223372036854775807 && !is_negative)
		return (-1);
	if (number > 9223372036854775807 && is_negative)
		return (0);
	if (is_negative)
		return ((int) -number);
	return ((int) number);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				is_negative;
	unsigned long	number;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	is_negative = 0;
	if (str[i] == '-')
		is_negative = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	number = 0;
	while (is_numeric(str[i]))
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (handle_long_overflow(number, is_negative));
}
