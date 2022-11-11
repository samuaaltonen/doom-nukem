/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:57:31 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/11 14:23:02 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_titlescreen(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	change_font(app, 80, 0xFF111111);
	render_text(app, (t_point){484, 214}, "AWAKE");
	change_font(app, 80, 0xFFd50000);
	render_text(app, (t_point){490, 210}, "AWAKE");
	change_font(app, 32, 0xFFFFFFFF);
	render_text(app, (t_point){504, WIN_H - 170}, "PRESS SPACE");
	load_font(app);
	play_music(app, MUSIC_PATH);
}

void	render_mainmenu(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	rect_from_surface(app->assets.button_idle, &src);
	render_prompt(app, (t_point){28, 78}, 2);
	change_font(app, 64, 0xFFd50000);
	render_text(app, (t_point){50, 100}, "AWAKE");
	button_function(app,
		render_button(app, (t_point){50, 180}, 2, "START GAME"), start_game);
	button_function(app,
		render_button(app, (t_point){50, 260}, 2, "LEVEL EDITOR"), do_nothing);
	button_function(app,
		render_button(app, (t_point){50, 340}, 2, "OPTIONS"), do_nothing);
	button_function(app,
		render_button(app, (t_point){50, 420}, 2, "QUIT GAME"), exit_game);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}

void	render_game(t_app *app)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	handle_movement(app);
	render_sectors(app);
	render_ui(app);
}

void	render_pausemenu(t_app *app)
{	
	t_rect		src;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	render_sectors(app);
	change_font(app, 16, 0xFF00FFFF);
	rect_from_surface(app->assets.button_idle, &src);
	render_prompt(app, (t_point){28, 78}, 2);
	button_function(app,
		render_button(app, (t_point){50, 100}, 2, "MAIN MENU"), main_menu);
	button_function(app,
		render_button(app, (t_point){50, 180}, 2, "CONTINUE"), pause_game);
	button_function(app,
		render_button(app, (t_point){50, 260}, 2, "SELECT LEVEL"), do_nothing);
	button_function(app,
		render_button(app, (t_point){50, 340}, 2, "OPTIONS"), do_nothing);
	button_function(app,
		render_button(app, (t_point){50, 420}, 2, "QUIT GAME"), exit_game);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
	render_ui(app);
}
