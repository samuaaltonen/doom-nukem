/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:55:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:13:31 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_the_rest(char **ftoa, int log, int precision, t_superint **m)
{
	int	i;

	i = 0;
	while ((*ftoa)[i])
		i++;
	while ((log >= 0 && i <= (log + precision))
		|| (i <= precision))
	{
		(*ftoa)[i] = '0';
		i++;
	}
	ft_superint_destroy(m);
	return (*ftoa);
}

static char	*division_to_string(int log10, int precision, t_superint **n,
								t_superint **d)
{
	t_superint	*mod;
	t_ull		result;
	int			i;
	char		*ftoa;

	if (log10 > 0)
		ftoa = ft_strnew(log10 + precision + 2);
	else
		ftoa = ft_strnew(precision + 3);
	mod = ft_superint_new(0, 3);
	if (!ftoa || !mod)
		return (NULL);
	i = -1;
	while ((log10 >= 0 && ++i <= (log10 + precision))
		|| (++i <= precision))
	{
		if (ft_superint_iszero(n))
			return (skip_the_rest(&ftoa, log10, precision, &mod));
		if (ft_superint_divide_samesize(n, d, &mod, &result) <= 0
			|| !ft_superint_clone(n, &mod) || !ft_superint_multiply_int(n, 10))
			return (NULL);
		ft_append_char(&ftoa, '0' + result);
	}
	ft_superint_destroy(&mod);
	return (ftoa);
}

static void	set_zeroes_and_dot(int log10, int precision, char **ftoa)
{
	char	*temp;
	char	*filled;
	int		i;
	int		len;

	if (log10 < 0)
	{
		len = ft_strlen(*ftoa);
		filled = ft_strnew(len - log10 + 1);
		ft_memmove(filled + -log10 + 1, *ftoa, len);
		i = 0;
		while (i <= -log10)
		{
			filled[i] = '0';
			i++;
		}
		filled[1] = '.';
		temp = *ftoa;
		*ftoa = filled;
		free(temp);
		return ;
	}
	ft_memmove(*ftoa + log10 + 2, *ftoa + log10 + 1, precision + 1);
	(*ftoa)[log10 + 1] = '.';
}

char	*ft_ftoa_positive(long double number, int precision)
{
	t_superint	*num;
	t_superint	*denum;
	int			log10;
	char		*str;

	log10 = ft_log10(number);
	if (!ft_ftdiv(number, &num, &denum)
		|| !ft_ftdiv_scale(log10, &num, &denum)
		|| !ft_ftdiv_logcheck(&log10, &num, &denum))
		return (NULL);
	if (ft_iszero(number))
		ft_superint_zero(&num);
	str = division_to_string(log10, precision + 1, &num, &denum);
	if (!str)
		return (NULL);
	set_zeroes_and_dot(log10, precision, &str);
	if (log10 < 0)
		ft_fa_round(&str, precision + 2, 0, !ft_superint_iszero(&num));
	else
		ft_fa_round(&str, log10 + precision + 2, 0, !ft_superint_iszero(&num));
	ft_fa_trim(&str, precision + 1);
	ft_superint_destroy(&num);
	ft_superint_destroy(&denum);
	return (str);
}

/*
 * Converts long double into string with given precision.
*/
char	*ft_ftoa(long double number, int precision)
{
	char	*ftoa;
	char	*joined;

	if (number < 0)
	{
		ftoa = ft_ftoa_positive(-number, precision);
		joined = ft_strjoin("-", ftoa);
		free(ftoa);
		return (joined);
	}
	return (ft_ftoa_positive(number, precision));
}
