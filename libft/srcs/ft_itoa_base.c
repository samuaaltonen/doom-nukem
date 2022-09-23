/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:49:53 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/04 16:49:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(unsigned long long n, int base)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n != 0)
	{
		n = n / base;
		digits++;
	}
	return (digits);
}

static void	append_digit(char **ptr, unsigned long long n, int base)
{
	char	*str;
	int		last_empty;

	str = *ptr;
	if (n >= (unsigned int) base)
		append_digit(ptr, n / base, base);
	last_empty = 0;
	while (str[last_empty])
		last_empty++;
	if (n % base < 10)
		str[last_empty] = n % base + '0';
	else if (n % base >= 36)
		str[last_empty] = (n % base - 36) + 'a';
	else
		str[last_empty] = (n % base - 10) + 'A';
}

/*
 * Converts given integer to given base. Supports up to long long integers.
 * example usage for converting decimal to hexadecimal:
 * ft_itoa_base(123, 16);
*/
char	*ft_itoa_base(long long number, int base)
{
	int		digits;
	char	*str;

	if (number < 0)
		digits = count_digits(-number, base);
	else
		digits = count_digits(number, base);
	str = ft_strnew(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	if (number < 0)
		str[0] = '-';
	if (number < 0)
		append_digit(&str, -number, base);
	else
		append_digit(&str, number, base);
	str[digits] = '\0';
	return (str);
}

/*
 * Same as ft_itoa_base but supports unsigned long long integers with an option
 * to add minus sign to the string (when isneg is set to 1)
*/
char	*ft_itoa_base_ull(unsigned long long number, int base, int isneg)
{
	int		digits;
	char	*str;

	digits = count_digits(number, base);
	str = ft_strnew(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	if (isneg)
		str[0] = '-';
	append_digit(&str, number, base);
	str[digits] = '\0';
	return (str);
}
