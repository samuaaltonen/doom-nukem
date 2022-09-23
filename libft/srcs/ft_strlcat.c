/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:33:34 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/19 12:33:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int	dst_len;
	int	i;
	int	append_count;

	dst_len = ft_strlen(dst);
	if (dst_len > (int) size)
		dst_len = (int) size;
	append_count = (int) size - dst_len - 1;
	i = 0;
	while (i < append_count && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (size > 0 && i <= append_count)
		dst[dst_len + i] = '\0';
	return ((size_t)(dst_len + ft_strlen(src)));
}
