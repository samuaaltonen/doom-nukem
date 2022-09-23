/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_anybase.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 13:09:33 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Handles anybase conversion. Converts given base-10 integer to any base.
 * Base is given as precision. Supports bases from 2 to 62.
*/
void	conversion_anybase(t_conf *conf)
{
	int			len;
	char		*itoa;
	long long	number;

	number = get_va_arg(conf);
	if (conf->precision <= 1 || conf->precision > 62)
		conf->precision = 2;
	itoa = ft_itoa_base(number, conf->precision);
	if (!itoa)
		return ;
	len = ft_strlen(itoa);
	if (!number && conf->precision == 0)
		len = 0;
	if (conf->width - len > 0 && !conf->flag_leftadjusted
		&& !conf->flag_zeropadded)
		out_char_repeat(' ', conf->width - len, conf);
	if (conf->width - len > 0 && !conf->flag_leftadjusted
		&& conf->flag_zeropadded)
		out_char_repeat('0', conf->width - len, conf);
	if (!(!number && conf->precision == 0))
		out_str(itoa, conf);
	if (conf->width - len > 0 && conf->flag_leftadjusted)
		out_char_repeat(' ', conf->width - len, conf);
	free(itoa);
}
