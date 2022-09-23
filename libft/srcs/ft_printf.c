/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:22:10 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:37:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_args(t_conf *conf, char **cursor)
{
	if (!(*cursor) || !(**cursor))
		return ;
	if (**cursor == '{')
		handle_color(conf, cursor);
	if (**cursor != '%')
	{
		out_char(**cursor, conf);
		(*cursor)++;
		return ;
	}
	(*cursor)++;
	ft_printf_reset_conf(conf);
	handle_flags(conf, cursor);
	handle_width(conf, cursor);
	handle_precision(conf, cursor);
	handle_length(conf, cursor);
	handle_flags(conf, cursor);
	handle_conversion(conf, cursor);
}

/*
 * Prints given format string with optional arguments.
 * Conversion specification is:
 * %[$][flags][width][.precision][length modifier]conversion
*/
int	ft_printf(const char *format, ...)
{
	t_conf	*conf;
	char	*cursor;
	int		n;

	if (!ft_printf_init_conf(&conf))
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	conf->fd = DEFAULT_FD;
	cursor = (char *) format;
	va_start(conf->ap, format);
	while (*cursor)
		handle_args(conf, &cursor);
	va_end(conf->ap);
	n = conf->n;
	free(conf);
	return (n);
}

/*
 * Prints given format string to specific file descriptor with optional
 * arguments.
 * Conversion specification is:
 * %[$][flags][width][.precision][length modifier]conversion
*/
int	ft_dprintf(int fd, const char *format, ...)
{
	t_conf	*conf;
	char	*cursor;
	int		n;

	if (!ft_printf_init_conf(&conf))
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	conf->fd = fd;
	cursor = (char *) format;
	va_start(conf->ap, format);
	while (*cursor)
		handle_args(conf, &cursor);
	va_end(conf->ap);
	n = conf->n;
	free(conf);
	return (n);
}
