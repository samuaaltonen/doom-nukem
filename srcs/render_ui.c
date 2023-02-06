/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/06 16:55:38 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Renders all elements of the HUD
*/
void	render_ui(t_app *app)
{
	render_crosshair(app);
	render_text_prompt(app, (t_rect){10, 10, 112, 32}, 1, app->conf->fps_info);
	render_player_status(app);
	render_equipment(app);
}

void	render_text_prompt(t_app *app, t_rect area, int size, char *text)
{
	render_ui_frame(app, area, size, DARK_GREY);
	area.x += size * 12;
	area.y += size * 12;
	area.w -= size * 12;
	area.h -= size * 12;
	change_font(app, 16, CYAN);
	render_text(app, area, text);
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

void	render_crosshair(t_app *app)
{
	t_rect	dst;
	t_rect	src;

	rect_from_surface(app->assets.crosshair, &src);
	dst.x = WIN_W / 2 - src.w / 2;
	dst.y = WIN_H / 2 - src.h / 2;
	dst.w = src.w;
	dst.h = src.h;
	blit_surface(app->assets.crosshair, &src, app->surface, &dst);
}

void	render_ui_element(t_app *app, SDL_Surface *elem, t_rect area)
{
	t_rect	src;

	rect_from_surface(elem, &src);
	blit_surface(elem, &src, app->surface, &area);
}
