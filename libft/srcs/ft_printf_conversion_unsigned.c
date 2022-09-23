/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:03:23 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	unsigned_output(t_conf *conf, unsigned long long number)
{
	if (number >= 10)
		unsigned_output(conf, number / 10);
	out_char(number % 10 + '0', conf);
}

static int	unsigned_width(t_conf *conf, long long number)
{
	int	width;

	width = ft_count_digits(number);
	if (conf->precision > width)
		width = conf->precision;
	return (width);
}

static void	unsigned_output_zeroes(t_conf *conf, long long number)
{
	int	len;

	len = ft_count_digits(number);
	if (conf->precision > len)
		out_char_repeat('0', conf->precision - len, conf);
	if (conf->flag_zeropadded && conf->width > len)
		out_char_repeat('0', conf->width - len, conf);
}

/*
 * Handles unsigned decimal (u) conversion.
*/
void	conversion_unsigned(t_conf *conf)
{
	int					len;
	unsigned long long	number;

	number = get_va_arg_unsigned(conf);
	len = unsigned_width(conf, number);
	if (!number && conf->precision == 0)
		len--;
	if (conf->width > len
		&& !conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
	unsigned_output_zeroes(conf, number);
	if (!(!number && conf->precision == 0))
		unsigned_output(conf, number);
	if (conf->width > len
		&& conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
}

void	conversion_unsigned_capital_u(t_conf *conf)
{
	conf->length = 3;
	conversion_unsigned(conf);
}
