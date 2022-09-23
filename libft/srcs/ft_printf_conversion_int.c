/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:55:09 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Outputs integer up to long long. If number is LLONG_MIN -9223372036854775808
 * prints 9 and truncates number to -223372036854775808 until continues with
 * recursive printing.
*/
static void	int_output(t_conf *conf, long long number)
{
	if (number < 0)
	{
		if (number == (long long) -9223372036854775807 - 1)
		{
			out_char('9', conf);
			number = -223372036854775808;
		}
		number = -1 * number;
	}
	if (number >= 10)
		int_output(conf, number / 10);
	out_char(number % 10 + '0', conf);
}

static void	int_output_sign(t_conf *conf, long long number)
{
	if (number < 0 || conf->flag_addsign)
	{
		if (number < 0)
			out_char('-', conf);
		else
			out_char('+', conf);
	}
}

static int	int_width(t_conf *conf, long long number)
{
	int	width;

	width = ft_count_digits(number);
	if (conf->precision > width)
		width = conf->precision;
	if (conf->flag_addsign || number < 0)
		width++;
	if (!conf->flag_addsign && conf->flag_addspace)
		width++;
	return (width);
}

static void	int_output_zeroes(t_conf *conf, long long number)
{
	int	len;

	len = ft_count_digits(number);
	if (conf->precision > len)
		out_char_repeat('0', conf->precision - len, conf);
	if (conf->flag_addspace)
		len++;
	if (conf->flag_zeropadded && conf->width > len)
	{
		if (number < 0 || conf->flag_addsign)
			out_char_repeat('0', conf->width - len - 1, conf);
		else
			out_char_repeat('0', conf->width - len, conf);
	}
}

/*
 * Handles signed decimal (d, i) conversion.
 *
 * Note: Adds zeropadding when precision is higher than digit count, even
 *       though when zeropadding flag is not set.
*/
void	conversion_int(t_conf *conf)
{
	int			len;
	long long	number;

	number = get_va_arg(conf);
	len = int_width(conf, number);
	if (!number && conf->precision == 0)
		len--;
	if (!conf->flag_addsign && conf->flag_addspace && number >= 0)
		out_char(' ', conf);
	if (conf->width > len
		&& !conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
	int_output_sign(conf, number);
	int_output_zeroes(conf, number);
	if (!(!number && conf->precision == 0))
		int_output(conf, number);
	if (conf->width > len
		&& conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
}
