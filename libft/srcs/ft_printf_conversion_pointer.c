/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:44:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pointer_precision(t_conf *conf, char **output)
{
	int		i;
	int		len;
	char	*zeros;
	char	*joined;

	if (conf->precision < 0)
		return ;
	len = ft_strlen(*output);
	if (conf->precision <= len)
		return ;
	zeros = ft_strnew(conf->precision - len);
	if (!zeros)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	i = 0;
	while (i < conf->precision - len)
	{
		zeros[i] = '0';
		i++;
	}
	joined = ft_strjoin(zeros, *output);
	if (!joined)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	free(*output);
	free(zeros);
	*output = joined;
}

static void	pointer_prefix(t_conf *conf, char **output, unsigned long long nbr)
{
	char	*joined;

	if (conf->flag_zeropadded && !conf->flag_leftadjusted)
	{
		out_str("0x", conf);
		conf->width -= 2;
		return ;
	}
	if (!nbr && ft_strlen(*output) == 1 && conf->precision == 0)
		(*output)[0] = '\0';
	joined = ft_strjoin("0x", *output);
	if (!joined)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	free(*output);
	*output = joined;
}

/*
 * Handles pointer conversion.
*/
void	conversion_pointer(t_conf *conf)
{
	int					len;
	char				*itoa;
	unsigned long long	number;

	number = va_arg(conf->ap, unsigned long long);
	itoa = ft_itoa_base_ull(number, 16, 0);
	if (!itoa)
		return ;
	pointer_precision(conf, &itoa);
	pointer_prefix(conf, &itoa, number);
	len = ft_strlen(itoa);
	if (!number && conf->precision == 0)
		len = 2;
	if (conf->width - len > 0 && !conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
	if (conf->width - len > 0 && !conf->flag_leftadjusted
		&& conf->flag_zeropadded)
		out_char_repeat('0', conf->width - len, conf);
	out_str_case(itoa, 0, conf);
	if (conf->width - len > 0 && conf->flag_leftadjusted)
		out_char_repeat(' ', conf->width - len, conf);
	free(itoa);
}
