/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fa_round.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:03:06 by saaltone          #+#    #+#             */
/*   Updated: 2022/03/14 15:07:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	prepend_one(char **number)
{
	char	*temp;

	temp = *number;
	*number = ft_strjoin("1", temp);
	free(temp);
	return (1);
}

static int	previous_digit_is_even(char **number, int index)
{
	if (index < 1)
		return (0);
	if ((*number)[index - 1] == '.')
		return (previous_digit_is_even(number, index - 1));
	if (((*number)[index - 1] + '0') % 2 == 0)
		return (1);
	return (0);
}

static int	round_down(char **number, int index)
{
	if (index < 0)
		return (0);
	(*number)[index] = '0';
	return (1);
}

/*
 * Rounds float to given precision. Float is inputted as ascii string. Returns
 * 1 if rounding has modified the string.
 * Uses bankers rounding (rounds to closes even number)
*/
int	ft_fa_round(char **number, int start, int leftover, int divnotzero)
{
	if (!number || (int) ft_strlen(*number) < start)
		return (0);
	if (start < 0)
		return (prepend_one(number));
	if ((*number)[start] == '.')
		return (ft_fa_round(number, start - 1, leftover, 0));
	if (!leftover)
	{
		if ((*number)[start] < '5')
			return (round_down(number, start));
		if ((*number)[start] == '5'
			&& previous_digit_is_even(number, start) && !divnotzero)
			return (round_down(number, start));
		(*number)[start] = '0';
		return (ft_fa_round(number, start - 1, 1, 0));
	}
	(*number)[start]++;
	if ((*number)[start] <= '9')
		return (1);
	(*number)[start] = '0';
	ft_fa_round(number, start - 1, 1, 0);
	return (0);
}

/*
 * Trims float (ascii-string) to given precision.
*/
void	ft_fa_trim(char **str, int precision)
{
	int	dot_pos;

	if (!str)
		return ;
	dot_pos = 0;
	while ((*str)[dot_pos] && (*str)[dot_pos] != '.')
		dot_pos++;
	if ((*str)[dot_pos] != '.')
		return ;
	if ((int) ft_strlen(*str) < dot_pos + precision)
		return ;
	(*str)[dot_pos + precision] = 0;
	if ((*str)[ft_strlen(*str) - 1] == '.')
		(*str)[ft_strlen(*str) - 1] = 0;
}
