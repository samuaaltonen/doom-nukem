/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:46:04 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 13:06:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	needle_len;

	if (!*needle)
		return ((char *) haystack);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i <= (int) len - (int) needle_len)
	{
		if (haystack[i] == needle[0]
			&& ft_strncmp(&(haystack[i]), needle, needle_len) == 0)
			return ((char *) &(haystack[i]));
		i++;
	}
	return (NULL);
}
