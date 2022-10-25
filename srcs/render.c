/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/25 13:31:37 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_titlescreen(t_app *app)
{
	t_rect		dst;
	t_rect		src;

		rect_from_surface(app->assets.title_screen_image, &src);
		rect_from_surface(app->surface, &dst);
		blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
		change_font(app, 64, 0xFF111111);
		render_text(app, (t_point){220, 80}, "DOOM NUKEM:");
		render_text(app, (t_point){260, 180}, "WORKING TITLE!");
		change_font(app, 64, 0xFFFF9400);
		render_text(app, (t_point){224, 84}, "DOOM NUKEM:");
		render_text(app, (t_point){264, 184}, "WORKING TITLE!");
		change_font(app, 32, 0xFFFFFFFF);
		render_text(app, (t_point){WIN_W / 2 - 5 * 36, WIN_H - 200}, "PRESS SPACE");
		load_font(app);
}

void	render_titlemenu(t_app *app)
{
	title_screen(app);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
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

void	render_game(t_app *app)
{
	handle_movement(app);
	render_sectors(app);
	render_ui(app);
}
