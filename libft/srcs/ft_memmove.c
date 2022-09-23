/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:25:55 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 10:38:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	size_t			char_i;

	if (!dst && !src && len > 0)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (dst > src)
			char_i = len - i - 1;
		else
			char_i = i;
		((unsigned char *) dst)[char_i] = ((unsigned char *) src)[char_i];
		i++;
	}
	return (dst);
}
