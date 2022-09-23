/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:46:23 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/10 14:26:52 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*mapped;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	mapped = (char *) malloc(len + 1);
	if (!mapped)
		return (0);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
