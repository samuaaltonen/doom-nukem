/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:23:36 by saaltone          #+#    #+#             */
/*   Updated: 2021/11/11 09:33:06 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

static int	count_until_next(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static int	append_word(char ***ptr, char const *s, char c, int word_index)
{
	int		i;
	int		word_len;
	char	**words;

	words = *ptr;
	word_len = count_until_next(s, c);
	words[word_index] = ft_strnew(sizeof(char) * word_len);
	if (!words[word_index])
		return (0);
	i = 0;
	while (s[i] != c && s[i])
	{
		words[word_index][i] = s[i];
		i++;
	}
	words[word_index][i] = '\0';
	return (1);
}

static char	**free_words(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**words;
	int		word_index;
	int		i;

	if (!s)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!words)
		return (0);
	i = 0;
	word_index = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			if (!append_word(&words, &(s[i]), c, word_index++))
				return (free_words(words));
		}
		i++;
	}
	words[word_index] = 0;
	return (words);
}
