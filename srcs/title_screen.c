/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/26 10:58:17 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	title_screen(t_app *app)
{
	t_rect		src;

	change_font(app, 16, 0xFFFF9400);
	rect_from_surface(app->assets.button_idle, &src);
	button_function(app, render_button(app, (t_point){50, 200}, 2), start_game);
	render_text(app, (t_point){74, 224}, "START GAME");
	button_function(app, render_button(app, (t_point){50, 300}, 2), start_game);
	render_text(app, (t_point){74, 324}, "SELECT LEVEL");
	button_function(app, render_button(app, (t_point){50, 400}, 2), start_game);
	render_text(app, (t_point){74, 424}, "OPTIONS");
	button_function(app, render_button(app, (t_point){50, 500}, 2), start_game);
	render_text(app, (t_point){74, 524}, "QUIT GAME");
}

void	button_function(t_app *app, t_rect button, void (*f)(t_app *app))
{
	if (check_mouse(app, button) && app->event.button.clicks == 1
		&& app->event.button.state == SDL_RELEASED)
	f(app);
}

void	start_game(t_app *app)
{
	app->status = STATUS_GAME;
}
