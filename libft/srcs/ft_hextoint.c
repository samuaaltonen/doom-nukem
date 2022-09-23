/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:55:05 by saaltone          #+#    #+#             */
/*   Updated: 2022/01/26 12:03:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hextoint(char *hex)
{
	int		len;
	int		i;
	int		value;
	char	c;

	i = 0;
	value = 0;
	len = ft_strlen(hex);
	while (i < len)
	{
		c = ft_toupper(hex[len - i - 1]);
		if (c > 'F' || c < '0' || (c > '9' && c < 'A'))
			return (0);
		if (c >= 'A')
			value += (c - 'A' + 10) * ft_pow(16, i);
		else
			value += (c - '0') * ft_pow(16, i);
		i++;
	}
	return (value);
}
