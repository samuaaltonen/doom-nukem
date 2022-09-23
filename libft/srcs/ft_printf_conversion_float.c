/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:55:08 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long double	init_float(t_conf *conf)
{
	long double	number;

	if (conf->length == 5)
		number = va_arg(conf->ap, long double);
	else
		number = va_arg(conf->ap, double);
	if (conf->precision < 0)
		conf->precision = 6;
	if (ft_floatsign(number))
	{
		conf->is_negative = 1;
		number = -number;
	}
	else
		conf->is_negative = 0;
	return (number);
}

static int	float_width(t_conf *conf, char	*ftoa)
{
	int	width;

	width = ft_strlen(ftoa);
	if (conf->precision > width)
		width = conf->precision;
	if (conf->is_negative || conf->flag_addsign)
		width++;
	if (conf->flag_addspace)
		width++;
	return (width);
}

static void	float_output_sign_zeroes(t_conf *conf, char *ftoa)
{
	int	len;

	if (!conf->flag_addsign && !conf->is_negative
		&& conf->flag_addspace)
		out_char(' ', conf);
	if (conf->is_negative || conf->flag_addsign)
	{
		if (conf->is_negative)
			out_char('-', conf);
		else
			out_char('+', conf);
	}
	len = ft_strlen(ftoa);
	if (conf->precision > len)
		out_char_repeat('0', conf->precision - len, conf);
	if (conf->flag_addspace)
		len++;
	if (conf->flag_zeropadded_override && conf->width > len)
	{
		if (conf->is_negative || conf->flag_addsign)
			out_char_repeat('0', conf->width - len - 1, conf);
		else
			out_char_repeat('0', conf->width - len, conf);
	}
}

static int	float_special_cases(char **ftoa, long double number, t_conf *conf)
{
	t_ldouble_cast	parts;

	parts.f = number;
	if (parts.s_parts.exponent == 32767)
	{
		if (parts.s_parts.mantissa == 0)
			*ftoa = ft_strdup("inf");
		else
		{
			*ftoa = ft_strdup("nan");
			conf->is_negative = 0;
			conf->flag_addsign = 0;
			conf->flag_addspace = 0;
		}
		conf->flag_hashtag = 0;
		conf->precision = 3;
		return (1);
	}
	return (0);
}

void	conversion_float(t_conf *conf)
{
	char		*ftoa;
	long double	number;
	int			len;

	number = init_float(conf);
	ftoa = NULL;
	if (!float_special_cases(&ftoa, number, conf))
	{
		ftoa = ft_ftoa(number, conf->precision);
		if (!ftoa)
			ft_printf_exit_error(MSG_ALLOC_FAILED);
	}
	len = float_width(conf, ftoa);
	if (conf->width > len && !conf->flag_leftadjusted
		&& !conf->flag_zeropadded_override)
		out_char_repeat(' ', conf->width - len, conf);
	float_output_sign_zeroes(conf, ftoa);
	out_str(ftoa, conf);
	if (conf->width > len && conf->flag_leftadjusted
		&& !conf->flag_zeropadded_override)
		out_char_repeat(' ', conf->width - len, conf);
	if (conf->flag_hashtag && conf->precision == 0)
		out_char('.', conf);
	if (ftoa)
		free(ftoa);
}
