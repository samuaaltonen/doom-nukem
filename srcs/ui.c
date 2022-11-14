/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/14 12:34:09 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_ui(t_app *app)
{
	render_ui_frame(app, (t_rect){10, 10, 112, 32}, 1);
	change_font(app, 16, 0xFF00FFFF);
	render_text(app, (t_point){24, 20},  app->conf->fps_info);
	load_font(app);
}

void	render_ui_frame(t_app *app,t_rect area, int size)
{
	t_rect	dst;
	t_rect	src;

	
	//frame_background();
	int	x;
	int	y;
	int top;
	int bottom;

	x = area.x;
	y = area.y;
	top = 8 * size;
	bottom = 0;
	while (y < area.y + area.h)
	{
		while (x < area.x + area.w)
		{
			if (x < area.x + area.w - top)
				put_pixel_to_surface(app->surface, x, y, 0xFF242424);
			x++;
		}
		top--;
		if (y > area.y + area.h - 8 * size)
		{
			x = area.x + bottom;
			bottom++;
		}
		else
			x = area.x;
		y++;
	}
	size *= 10;
	//frame_top();
	dst.x = area.x;
	dst.y = area.y;
	dst.w = size;
	dst.h = size;
	src.x = 0;
	src.y = 0;
	src.w = 10;
	src.h = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + size;
	dst.w = area.w - 2 * size;
	src.x = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + dst.w + size;
	dst.w = size;
	src.x = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	//frame_mid();
	dst.x = area.x;
	dst.y = area.y + size;
	dst.h = area.h - 2 * dst.h;
	src.x = 0;
	src.y = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + area.w - size;
	src.x = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	//frame_bottom();
	dst.x = area.x;
	dst.y = area.y + area.h - size;
	dst.w = size;
	dst.h = size;
	src.x = 0;
	src.y = 20;
	src.w = 10;
	src.h = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + size;
	dst.y = area.y + area.h - size;
	dst.w = area.w - 2 * dst.w;
	src.x = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + area.w - size;
	dst.y = area.y + area.h - size;
	dst.w = size;
	dst.h = size;
	src.x = 20;
	src.y = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
}

t_rect	render_button(t_app *app, t_point pos, int size, char *text)
{
	t_rect		dst;
	t_rect		src;
	t_point		text_pos;

	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = app->assets.button_idle->w * size;
	dst.h = app->assets.button_idle->h * size;
	text_pos.x = pos.x + 12 * size;
	text_pos.y = pos.y + 12 * size;
	rect_from_surface(app->assets.button_idle, &src);
	change_font(app, 16, 0xFF00FFFF);
	if (!check_mouse(app, dst))
		blit_surface(app->assets.button_idle, &src, app->surface, &dst);
	else if (check_mouse(app, dst))
	{
		change_font(app, 16, 0xFF8BC34A);
		if (((SDL_GetMouseState(NULL, NULL)) & SDL_BUTTON_LMASK) != 0)
			blit_surface(app->assets.button_press, &src, app->surface, &dst);
		else
		{
			blit_surface(app->assets.button_select, &src, app->surface, &dst);
			change_font(app, 16, 0xFFD50000);
		}
			
	}
	render_text(app, text_pos, text);
	load_font(app);
	return (dst);
}

void	render_pointer(t_app *app, int x, int y)
{
	t_rect		dst;
	t_rect		src;
	
	rect_from_surface(app->assets.pointer, &src);
	dst.x = x;
	dst.y = y;
	dst.w = app->assets.pointer->w;
	dst.h = app->assets.pointer->h;
	blit_surface(app->assets.pointer, &src, app->surface, &dst);
}

int	check_mouse(t_app *app, t_rect rect)
{
	if (app->mouse_pos.x >= rect.x
		&& app->mouse_pos.y >= rect.y
		&& app->mouse_pos.x <= (rect.x + rect.w)
		&& app->mouse_pos.y <= (rect.y + rect.h))
		return (1);
	return (0);
}
