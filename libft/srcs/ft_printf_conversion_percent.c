/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 12:28:13 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_percent(t_conf *conf)
{
	char	left_filler;

	left_filler = ' ';
	if (conf->flag_zeropadded || conf->flag_zeropadded_override)
		left_filler = '0';
	if (conf->width - 1 > 0 && !conf->flag_leftadjusted)
		out_char_repeat(left_filler, conf->width - 1, conf);
	out_char('%', conf);
	if (conf->width - 1 > 0 && conf->flag_leftadjusted)
		out_char_repeat(' ', conf->width - 1, conf);
}
