/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:05:23 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/11 13:58:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int	s1_end;
	int	i;

	s1_end = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[s1_end + i] = s2[i];
		i++;
	}
	s1[s1_end + i] = '\0';
	return (s1);
}
