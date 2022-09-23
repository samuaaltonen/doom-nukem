/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:49:16 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/19 17:18:24 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

static int	w_spaces_beginning(char const *s)
{
	int	i;

	i = 0;
	while (is_whitespace(s[i]))
		i++;
	return (i);
}

static int	w_spaces_end(char const *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (is_whitespace(s[len - 1 - i]))
		i++;
	return (i);
}

char	*ft_strtrim(char const *s)
{
	char	*trimmed;
	int		i;
	int		w_b;
	int		w_e;
	int		len;

	if (!s)
		return (NULL);
	w_b = w_spaces_beginning(s);
	w_e = w_spaces_end(s);
	len = ft_strlen(s);
	if (w_b + w_e >= len)
		return (ft_strnew(0));
	trimmed = ft_strnew(sizeof(char) * (len - w_b - w_e));
	if (!trimmed)
		return (0);
	i = 0;
	while (i < len - w_b - w_e)
	{
		trimmed[i] = s[i + w_b];
		i++;
	}
	return (trimmed);
}
