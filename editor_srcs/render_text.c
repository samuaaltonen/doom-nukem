/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:48:08 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/01 16:48:16 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static t_rect	get_rect(int c);
static void		render_char(t_app *app, t_point *position, t_rect src);
static t_rect	get_char(char *str, int c, int line);
static int		get_word_index(char *text, int index);

void	render_text(t_app *app, t_rect frame, char *text)
{
	int		i;
	t_point	pos;

	pos = (t_point){frame.x, frame.y};
	i = 0;
	while (text[i] != '\0')
	{
		if (i > 0 && text[i - 1] == ' '
			&& pos.x + 12 * (get_word_index(text, i) - i) > frame.x + frame.w)
		{
			pos = (t_point){frame.x, pos.y + app->assets.font.size * 1.25};
			if (text[i] == ' ')
				i++;
		}
		if (text[i] == '\n')
		{
			pos = (t_point){frame.x, pos.y + app->assets.font.size * 1.25};
			i++;
		}
		if (pos.y + app->assets.font.size > frame.y + frame.h)
			break ;
		render_char(app, &pos, get_rect(text[i]));
		i++;
	}
}

static t_rect	get_rect(int c)
{
	t_rect	rect;
	char	*upcase;
	char	*lowcase;
	char	*digits;
	char	*symbols;

	upcase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	lowcase = "abcdefghijklmnopqrstuvwxyz";
	digits = "0123456789";
	symbols = ".,:;'\"!?-_()/|\\<>\%";
	if (ft_isupper(c))
		rect = get_char(upcase, c, 0);
	else if (ft_islower(c))
		rect = get_char(lowcase, c, 1);
	else if (ft_isdigit(c))
		rect = get_char(digits, c, 2);
	else
		rect = get_char(symbols, c, 3);
	return (rect);
}

static void	render_char(t_app *app, t_point *position, t_rect src)
{
	t_rect	dst;

	dst.x = position->x;
	dst.y = position->y;
	dst.w = src.w * app->assets.font.size / 16;
	dst.h = app->assets.font.size;
	blit_surface(app->assets.font.font, &src, app->surface, &dst);
	position->x += src.w * app->assets.font.size / 16;
}

static t_rect	get_char(char *str, int c, int line)
{
	t_rect	src;
	int		width;
	int		i;

	if (line == 0)
		width = 12;
	else if (line == 1 || line == 2)
		width = 10;
	else
		width = 8;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i]) == c)
			src.x = i * 16;
		i++;
	}
	if (c == ' ')
		src.x = i * 16;
	src.y = line * 16;
	src.w = width;
	src.h = 16;
	return (src);
}

static int	get_word_index(char *text, int index)
{
	while (text[index] != ' ' && text[index] != '\0')
		index++;
	return (index);
}
