/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:48:08 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/28 00:24:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static t_rect	get_rect(int c);
static void		render_char(t_app *app, t_point *position, t_rect src);
static t_rect	get_char(char *str, int c, int line);

void	render_text(t_app *app, t_point position, char *text)
{
	int		i;

	i = 0;
	while (text[i] != '\0')
	{
//		if (ft_strchr(upcase, text[i]))
			render_char(app, &position, get_rect(text[i]));
//		position.x += app->assets.font.size - 4;
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


void	change_font(t_app *app, int size, int color)
{
	int		x;
	int		y;
	int		pixel_pos;
	char	*pixel;

	app->assets.font.size = size;
	x = 0;
	y = 0;
	while (y < app->assets.font.font->h)
	{
		while (x < app->assets.font.font->w)
		{
			pixel_pos = (y * app->assets.font.font->pitch) + (x * IMAGE_PIXEL_BYTES);
			pixel = app->assets.font.font->pixels + pixel_pos;
			if ((*(int *)pixel & 0xFF000000) != 0x00000000)
				put_pixel_to_surface(app->assets.font.font, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
}
