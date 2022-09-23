/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:38:20 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(t_conf *conf, char *str, int len)
{
	int		i;
	char	left_filler;

	left_filler = ' ';
	if (conf->flag_zeropadded || conf->flag_zeropadded_override)
		left_filler = '0';
	if (conf->width - len > 0 && !conf->flag_leftadjusted)
		out_char_repeat(left_filler, conf->width - len, conf);
	i = 0;
	while (i < len)
	{
		out_char(str[i], conf);
		i++;
	}
	if (conf->width - len > 0 && conf->flag_leftadjusted)
		out_char_repeat(' ', conf->width - len, conf);
}

void	conversion_string(t_conf *conf)
{
	char	*str;
	int		len;

	str = va_arg(conf->ap, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (conf->precision >= 0 && len > conf->precision)
		len = conf->precision;
	print_str(conf, str, len);
}
