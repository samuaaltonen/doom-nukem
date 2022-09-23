/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 13:15:23 by saaltone          #+#    #+#             */
/*   Updated: 2022/05/30 13:33:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	has_closing_bracket(char **cursor)
{
	int	i;

	i = 1;
	while ((*cursor)[i])
	{
		if ((*cursor)[i] == '{')
			return (0);
		if ((*cursor)[i] == '}')
			return (1);
		i++;
	}
	return (0);
}

static char	*get_color_str(char **cursor)
{
	int		i;
	char	*color;

	i = 0;
	while ((*cursor)[i])
	{
		if ((*cursor)[i] == '}')
			break ;
		i++;
	}
	if (i > 10)
		return (NULL);
	color = ft_strnew(i);
	if (!color)
		ft_printf_exit_error(MSG_ALLOC_FAILED);
	i = 0;
	while ((*cursor)[i + 1])
	{
		if ((*cursor)[i + 1] == '}')
			break ;
		color[i] = (*cursor)[i + 1];
		i++;
	}
	return (color);
}

static int	match_color(t_conf *conf, const t_color_identifier *colors,
	char *color)
{
	int	i;

	i = 0;
	while (colors[i].identifier)
	{
		if (!ft_strcmp(colors[i].identifier, color))
		{
			out_str(colors[i].color, conf);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	output_color(t_conf *conf, char *color)
{
	static const t_color_identifier	colors[] = {
	{"black", COLOR_BLACK},
	{"red", COLOR_RED},
	{"green", COLOR_GREEN},
	{"yellow", COLOR_YELLOW},
	{"blue", COLOR_BLUE},
	{"purple", COLOR_PURPLE},
	{"cyan", COLOR_CYAN},
	{"white", COLOR_WHITE},
	{"bg_black", BG_BLACK},
	{"bg_red", BG_RED},
	{"bg_green", BG_GREEN},
	{"bg_yellow", BG_YELLOW},
	{"bg_blue", BG_BLUE},
	{"bg_purple", BG_PURPLE},
	{"bg_cyan", BG_CYAN},
	{"bg_white", BG_WHITE},
	{"reset", COLOR_RESET},
	{"eoc", COLOR_RESET},
	{0, NULL},
	};

	return (match_color(conf, colors, color));
}

void	handle_color(t_conf *conf, char **cursor)
{
	char	*color_str;

	if (!has_closing_bracket(cursor))
		return ;
	color_str = get_color_str(cursor);
	if (!color_str)
		return ;
	if (output_color(conf, color_str))
		*cursor += ft_strlen(color_str) + 2;
	free(color_str);
}
