/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/06 16:54:11 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	button_function(t_app *app, t_rect button, void (*f)(t_app *app))
{
	if (check_mouse(app, button))
	{
		if (app->conf->buttonstates & LEFT_MOUSE)
			start_timer(&app->button_timer, 0.5);
		else if (!(app->conf->buttonstates & LEFT_MOUSE)
			&& !check_timer(&app->button_timer))
		{
			f(app);
			start_timer(&app->button_timer, 0.0);
		}	
	}
}

void	start_game(t_app *app)
{
	player_init(app);
	init_enemies(app);
	init_bullets(app);
	weapon(app, 1);
	app->status = STATUS_GAME;
}

void	exit_game(t_app *app)
{
	if (app)
		exit(EXIT_SUCCESS);
}

/**
 * @brief Checks if the mouse is within the given rectangle.
 * Returns 1 if true or 0 if false.
 * 
 * @param app
 * @param rect
 * @return int
 */
int	check_mouse(t_app *app, t_rect rect)
{
	if (app->mouse_pos.x >= rect.x
		&& app->mouse_pos.y >= rect.y
		&& app->mouse_pos.x <= (rect.x + rect.w)
		&& app->mouse_pos.y <= (rect.y + rect.h))
		return (1);
	return (0);
}

t_rect	render_button(t_app *app, t_rect area, int size, char *text)
{
	t_rect	text_pos;

	change_font(app, 16, CYAN);
	text_pos.x = area.x + size * 12;
	text_pos.y = area.y + area.h / 2 - size * 12 / 2;
	text_pos.w = area.w;
	text_pos.h = area.h;
	if (!check_mouse(app, area))
		color_surface(app->assets.ui_frame, CYAN);
	else if (check_mouse(app, area))
	{
		change_font(app, 16, GREEN);
		if (((SDL_GetMouseState(NULL, NULL)) & SDL_BUTTON_LMASK) != 0)
			color_surface(app->assets.ui_frame, GREEN);
		else
		{
			color_surface(app->assets.ui_frame, DARK_RED);
			change_font(app, 16, DARK_RED);
		}		
	}
	render_ui_frame(app, area, size, 0);
	render_text(app, text_pos, text);
	color_surface(app->assets.ui_frame, CYAN);
	return (area);
}
