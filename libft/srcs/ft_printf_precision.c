/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:08:09 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	move_cursor_to_nondigit(char **cursor)
{
	if (ft_isdigit(**cursor))
	{
		(*cursor)++;
		move_cursor_to_nondigit(cursor);
	}
}

/*
 * Parses precision and saves it to conf.
*/
void	handle_precision(t_conf *conf, char **cursor)
{
	int	digits;

	if (**cursor != '.')
		return ;
	conf->precision = -1;
	(*cursor)++;
	if (**cursor == '*')
	{
		conf->precision = va_arg(conf->ap, int);
		(*cursor)++;
		return ;
	}
	conf->flag_zeropadded = 0;
	conf->precision = ft_atoi(*cursor);
	digits = ft_count_digits(conf->precision);
	if (!ft_isdigit(**cursor))
		digits = 0;
	*cursor += digits;
	move_cursor_to_nondigit(cursor);
	if (**cursor == '*')
	{
		va_arg(conf->ap, int);
		(*cursor)++;
	}
	handle_precision(conf, cursor);
}
