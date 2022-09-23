/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:34:00 by saaltone          #+#    #+#             */
/*   Updated: 2022/02/15 20:51:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits_and_sign(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

static void	append_digit(char **ptr, int n)
{
	char	*str;
	int		last_empty;

	str = *ptr;
	if (n >= 10)
		append_digit(ptr, n / 10);
	last_empty = 0;
	while (str[last_empty])
		last_empty++;
	str[last_empty] = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*str;

	digits = count_digits_and_sign(n);
	str = ft_strnew(sizeof(char) * digits);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[1] = '2';
			n = -147483648;
		}
		n = n * -1;
	}
	append_digit(&str, n);
	str[digits] = '\0';
	return (str);
}
