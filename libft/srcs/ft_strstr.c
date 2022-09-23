/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:06:04 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/04 10:44:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	j;
	int	maybe_found;

	if (!*needle)
		return ((char *) haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			maybe_found = 1;
			while (needle[j])
			{
				if (needle[j] != haystack[i + j])
					maybe_found = 0;
				j++;
			}
			if (maybe_found)
				return ((char *) &(haystack[i]));
		}
		i++;
	}
	return (NULL);
}
