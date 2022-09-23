/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_octal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:06:14 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	octal_precision(t_conf *conf, char **output)
{
	int		i;
	int		len;
	char	*zeros;
	char	*joined;

	if (conf->precision < 0)
		return ;
	len = ft_strlen(*output);
	if (conf->precision > len)
	{
		zeros = ft_strnew(conf->precision - len);
		if (!zeros)
			ft_printf_exit_error(MSG_ALLOC_FAILED);
		i = -1;
		while (++i < conf->precision - len)
			zeros[i] = '0';
		joined = ft_strjoin(zeros, *output);
		if (!joined)
			ft_printf_exit_error(MSG_ALLOC_FAILED);
		free(*output);
		free(zeros);
		*output = joined;
	}
}

static void	octal_prefix(t_conf *conf, char **output, unsigned long long nbr)
{
	char	*joined;

	if (!nbr)
		return ;
	if (conf->flag_hashtag
		&& (**output != '0' || (!nbr && conf->precision == 0)))
	{
		joined = ft_strjoin("0", *output);
		if (!joined)
			ft_printf_exit_error(MSG_ALLOC_FAILED);
		free(*output);
		*output = joined;
	}
}

static void	octal_width(t_conf *conf, char **itoa, unsigned long long number,
						int *len)
{
	if (*itoa && !number && conf->precision == 0 && !conf->flag_hashtag)
	{
		**itoa = '\0';
		*len = 0;
		return ;
	}
	*len = ft_strlen(*itoa);
}

/*
 * Handles octal conversion. Treats given numbers as unsigned.
*/
void	conversion_octal(t_conf *conf)
{
	int					len;
	char				*itoa;
	unsigned long long	number;

	number = get_va_arg_unsigned(conf);
	itoa = ft_itoa_base_ull(number, 8, 0);
	if (!itoa)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	octal_precision(conf, &itoa);
	octal_prefix(conf, &itoa, number);
	octal_width(conf, &itoa, number, &len);
	if (conf->width - len > 0
		&& !conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
	if (conf->width - len > 0
		&& !conf->flag_leftadjusted
		&& conf->flag_zeropadded)
		out_char_repeat('0', conf->width - len, conf);
	out_str_case(itoa, conf->is_uppercase, conf);
	if (conf->width - len > 0 && conf->flag_leftadjusted)
		out_char_repeat(' ', conf->width - len, conf);
	free(itoa);
}
