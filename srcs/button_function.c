/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/24 15:22:19 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	button_function(t_app *app, t_rect button, void (*f)(t_app *app))
{
	if (check_mouse(app, button))
	{
		if(app->event.button.clicks == 1)
		{
			if (app->event.button.state == SDL_RELEASED)
				f(app);
		}
	}
}

void	start_game(t_app *app)
{
	app->player = (t_player){(t_vector2){POSITION_START_X, POSITION_START_Y},
		(t_vector2){DIRECTION_START_X, DIRECTION_START_Y},
		(t_vector2){0.0, 0.0}, 1.0, 0.5f, 0.f, 0.5, 0, 0, 0, 0,
		(t_inventory){0,0,0,0,0,FALSE}};
	init_camera_plane(app);
	import_file(app, MAP_PATH);
	app->status = STATUS_GAME;
}

void	pause_game(t_app *app)
{
	if (app->status == STATUS_GAME || app->status == STATUS_GAMEOPTIONS)
		app->status = STATUS_PAUSEMENU;
	else if (app->status == STATUS_PAUSEMENU)
		app->status = STATUS_GAME;
}

void	exit_game(t_app *app)
{
	if (app)
		exit(EXIT_SUCCESS);
}

void	main_menu(t_app *app)
{
	app->status = STATUS_MAINMENU;
}

void	main_options(t_app *app)
{
	app->status = STATUS_MAINOPTIONS;
}

void	game_options(t_app *app)
{
	app->status = STATUS_GAMEOPTIONS;
}

void	fullscreen(t_app *app)
{
	if (!(SDL_GetWindowFlags(app->win) & SDL_WINDOW_FULLSCREEN))
	{
		SDL_DestroyWindow(app->win);
		app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, SDL_WINDOW_FULLSCREEN);
	}
	else if (SDL_GetWindowFlags(app->win) & SDL_WINDOW_FULLSCREEN)
	{
		SDL_DestroyWindow(app->win);
		app->win = SDL_CreateWindow(WIN_NAME, 0, 0, WIN_W, WIN_H, 0);
	}	
	app->surface = SDL_GetWindowSurface(app->win);
}

void	do_nothing(t_app *app)
{	
	if (app)
		return ;
}