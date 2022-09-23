/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:08:11 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_width_star(t_conf *conf, char **cursor)
{
	conf->width = va_arg(conf->ap, int);
	if (conf->width < 0)
	{
		conf->width *= -1;
		conf->flag_leftadjusted = 1;
		conf->flag_zeropadded = 0;
	}
	(*cursor)++;
}

/*
 * Parses width and saves it to conf.
*/
void	handle_width(t_conf *conf, char **cursor)
{
	if (**cursor == '*')
		handle_width_star(conf, cursor);
	if (ft_isdigit(**cursor))
	{
		conf->width = ft_atoi(*cursor);
		*cursor += ft_count_digits(conf->width);
	}
	if (**cursor == '*')
		handle_width_star(conf, cursor);
}
