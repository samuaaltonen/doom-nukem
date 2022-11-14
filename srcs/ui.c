/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/11 14:08:25 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_ui(t_app *app)
{
	render_button(app, (t_point){10, 10}, 1, app->conf->fps_info);
}

void	render_prompt(t_app *app, t_point pos, int size)
{
	t_rect		dst;
	t_rect		src;

	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = app->assets.text_prompt->w * size;
	dst.h = app->assets.text_prompt->h * size;
	rect_from_surface(app->assets.text_prompt, &src);
	blit_surface(app->assets.text_prompt, &src, app->surface, &dst);
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
