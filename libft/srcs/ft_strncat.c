/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:18:42 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/11 14:01:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	s1_end;
	size_t	i;

	s1_end = ft_strlen(s1);
	i = 0;
	while (s2[i] && i < n)
	{
		s1[s1_end + i] = s2[i];
		i++;
	}
	s1[s1_end + i] = '\0';
	return (s1);
}
