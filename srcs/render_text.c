/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:48:08 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/20 12:48:34 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void		render_char(t_app *app, t_point position, t_rect src);
static t_rect	get_char(char *str, int c);

void	render_text(t_app *app, t_point position, char *text)
{
	char	*str;
	char	c;
	int		i;

	str = "abcdefghijklmnopqrstuvwxyz0123456789.,:;'\"!?-_()/|\\";
	i = 0;
	while (text[i] != '\0')
	{
		c = ft_tolower(text[i]);
		if (ft_strchr(str, c))
			render_char(app, position, get_char(str, c));
		position.x += app->assets.font.size - 2;
		i++;
	}
}

static void	render_char(t_app *app, t_point position, t_rect src)
{
	t_rect	dst;

	dst.x = position.x;
	dst.y = position.y;
	dst.w = app->assets.font.size;
	dst.h = app->assets.font.size;
	blit_surface(app->assets.font.font, &src, app->surface, &dst);
}

static t_rect	get_char(char *str, int c)
{
	t_rect	src;
	int			font_offset;
	int			i;

	font_offset = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_tolower(str[i]) == c)
			font_offset = i;
		i++;
	}
	src.x = 12 * font_offset;
	src.y = 0;
	src.w = 14;
	src.h = 14;
	return (src);
}

void	load_font(t_app *app)
{
	if (!app->assets.font.font)
		app->assets.font.font = SDL_LoadBMP(TEXTURE_FONT);
	if (!app->assets.font.font)
		exit_error("Could not load font");
	app->assets.font.size = 14;
	change_font(app, 14, 0xFF000000);
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
