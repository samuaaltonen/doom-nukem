/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/27 11:05:14 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	button_function(t_app *app, t_rect button, void (*f)(t_app *app))
{
	if (check_mouse(app, button) && app->event.button.clicks == 1
		&& app->event.button.state == SDL_RELEASED)
		f(app);
}

void	start_game(t_app *app)
{
	app->player = (t_player){(t_vector2){POSITION_START_X, POSITION_START_Y},
		(t_vector2){DIRECTION_START_X, DIRECTION_START_Y},
		(t_vector2){0.0, 0.0}, 1.0, 0.5f,0.f, 0};
	init_camera_plane(app);
	import_file(app, MAP_PATH);
	app->status = STATUS_GAME;
}

void	pause_game(t_app *app)
{
	SDL_WarpMouseInWindow(app->win, WIN_W / 2, WIN_H / 2);
	if (app->status == STATUS_GAME)
		app->status = STATUS_PAUSEMENU;
	else if (app->status == STATUS_PAUSEMENU)
		app->status = STATUS_GAME;
}

void	exit_game(t_app *app)
{
	free(app);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	main_menu(t_app *app)
{
	app->status = STATUS_MAINMENU;
}

void	do_nothing(t_app *app)
{
	if (app)
		return ;
}
