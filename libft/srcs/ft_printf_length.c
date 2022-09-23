/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:07:05 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Uses va_arg to get given argument with correct lenght. For char and short
 * (hh, h) it gets the argument as int but then truncates it to char/short by
 * casting. (Because va_arg automatically promotes it to int)
*/
long long	get_va_arg(t_conf *conf)
{
	long long	temp;

	temp = 0;
	if (conf->length == 0)
		temp = va_arg(conf->ap, int);
	if (conf->length == 1)
		temp = (char) va_arg(conf->ap, int);
	if (conf->length == 2)
		temp = (short) va_arg(conf->ap, int);
	if (conf->length == 3)
		temp = va_arg(conf->ap, long);
	if (conf->length == 4)
		temp = va_arg(conf->ap, long long);
	if (temp < 0)
		conf->is_negative = 1;
	else
		conf->is_negative = 0;
	return (temp);
}

unsigned long long	get_va_arg_unsigned(t_conf *conf)
{
	unsigned long long	temp;

	temp = 0;
	if (conf->length == 0)
		temp = va_arg(conf->ap, unsigned int);
	if (conf->length == 1)
		temp = (unsigned char) va_arg(conf->ap, unsigned int);
	if (conf->length == 2)
		temp = (unsigned short) va_arg(conf->ap, unsigned int);
	if (conf->length == 3)
		temp = va_arg(conf->ap, unsigned long);
	if (conf->length == 4)
		temp = va_arg(conf->ap, unsigned long long);
	conf->is_negative = 0;
	return (temp);
}

/*
 * Handles length modifieds (l, llu, hh etc.):
 * hh	= (char)
 * h	= (short)
 * l	= (long)
 * ll	= (long long)
 * L	= (long double)
 * 
 * q	= synonym for ll
 * j	= intmax_t or uintmax_t
 * z	= size_t or ssize_t
*/
void	handle_length(t_conf *conf, char **cursor)
{
	if (!(*cursor) || !(**cursor == 'h' || **cursor == 'l' || **cursor == 'L'
			|| **cursor == 'q' || **cursor == 'j' || **cursor == 'z'))
		return ;
	if (conf->length == LENGTH_SHORT && **cursor == 'h')
		conf->length = LENGTH_CHAR;
	else if (conf->length < LENGTH_LONG && **cursor == 'h')
		conf->length = LENGTH_SHORT;
	if (conf->length == LENGTH_LONG && **cursor == 'l')
		conf->length = LENGTH_LONG_LONG;
	else if (**cursor == 'l')
		conf->length = LENGTH_LONG;
	if (**cursor == 'L')
		conf->length = LENGTH_LONG_DOUBLE;
	if (**cursor == 'q' || **cursor == 'j' || **cursor == 'z')
		conf->length = LENGTH_LONG_LONG;
	(*cursor)++;
	handle_length(conf, cursor);
}
