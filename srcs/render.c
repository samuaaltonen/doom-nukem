/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/01 17:48:58 by dpalacio         ###   ########.fr       */
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
	change_font(app, 80, 0xFF111111);
	render_text(app, (t_point){484, 216}, "AWAKE");
	change_font(app, 80, 0xFFd50000);
	render_text(app, (t_point){490, 210}, "AWAKE");
	change_font(app, 32, 0xFFFFFFFF);
	render_text(app, (t_point){504, WIN_H - 170}, "PRESS SPACE");
	load_font(app);
}

void	render_mainmenu(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	change_font(app, 16, 0xFF00FFFF);
	rect_from_surface(app->assets.button_idle, &src);
	button_function(app, render_button(app, (t_point){50, 200}, 2), start_game);
	render_text(app, (t_point){74, 224}, "START GAME");
	change_font(app, 16, 0xFF00FFFF);
	button_function(app, render_button(app, (t_point){50, 300}, 2), do_nothing);
	render_text(app, (t_point){74, 324}, "SELECT LEVEL");
	change_font(app, 16, 0xFF00FFFF);
	button_function(app, render_button(app, (t_point){50, 400}, 2), do_nothing);
	render_text(app, (t_point){74, 424}, "OPTIONS");
	change_font(app, 16, 0xFF00FFFF);
	button_function(app, render_button(app, (t_point){50, 500}, 2), exit_game);
	render_text(app, (t_point){74, 524}, "QUIT GAME");
	change_font(app, 16, 0xFF00FFFF);
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

void	render_pausemenu(t_app *app)
{	
	t_rect		src;

	render_sectors(app);
	change_font(app, 16, 0xFFFF9400);
	rect_from_surface(app->assets.button_idle, &src);
	button_function(app, render_button(app, (t_point){50, 100}, 2), main_menu);
	render_text(app, (t_point){74, 124}, "MAIN MENU");
	button_function(app, render_button(app, (t_point){50, 200}, 2), pause_game);
	render_text(app, (t_point){74, 224}, "CONTINUE");
	button_function(app, render_button(app, (t_point){50, 300}, 2), do_nothing);
	render_text(app, (t_point){74, 324}, "SELECT LEVEL");
	button_function(app, render_button(app, (t_point){50, 400}, 2), do_nothing);
	render_text(app, (t_point){74, 424}, "OPTIONS");
	button_function(app, render_button(app, (t_point){50, 500}, 2), exit_game);
	render_text(app, (t_point){74, 524}, "QUIT GAME");

	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
	render_ui(app);
}
