/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:49:16 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:34:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_exit_error(char	*message)
{
	ft_putstr(message);
	exit(EXIT_FAILURE);
}

void	out_char(char c, t_conf *conf)
{
	ft_putchar_fd(c, conf->fd);
	(conf->n)++;
}

void	out_char_repeat(char c, int repeat, t_conf *conf)
{
	int	i;

	i = 0;
	while (i < repeat)
	{
		ft_putchar_fd(c, conf->fd);
		i++;
	}
	conf->n += i;
}

void	out_str(char *str, t_conf *conf)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], conf->fd);
		(conf->n)++;
		i++;
	}
}

void	out_str_case(char *str, int is_uppercase, t_conf *conf)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		if (is_uppercase)
			out_char(ft_toupper(str[i]), conf);
		else
			out_char(ft_tolower(str[i]), conf);
		i++;
	}
}
