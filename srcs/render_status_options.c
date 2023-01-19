/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_options.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 17:03:18 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Renders option menu buttons.
 * 
 * @param app 
 */
static void	render_option_buttons(t_app *app)
{
	button_function(app,
		render_button(app, (t_rect){340, 200, 160, 32}, 1, "FULLSCREEN"),
		fullscreen);
	if (app->status == STATUS_MAINOPTIONS)
		button_function(app,
			render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"),
			main_menu);
	if (app->status == STATUS_GAMEOPTIONS)
	{
		button_function(app,
			render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"),
			pause_game);
		button_function(app,
			render_button(app, (t_rect){340, 264, 160, 32}, 1, "CONTROLS"),
			controls);
	}
}

/**
 * @brief Renders option menu.
 * 
 * @param app 
 */
void	render_options(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	if (app->status == STATUS_MAINOPTIONS)
		blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	else if (app->status == STATUS_GAMEOPTIONS)
		render_sectors(app);
	render_ui_frame(app, (t_rect){320, 132, 224, 64}, 1, DARK_GREY);
	change_font(app, 32, DARK_RED);
	render_text(app, (t_rect){336, 146, 800, 800}, "OPTIONS");
	render_ui_frame(app, (t_rect){320, 180, 640, 360}, 1, DARK_GREY);
	render_option_buttons(app);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}

/**
 * @brief Renders control list.
 * 
 * @param app 
 */
void	render_controls(t_app *app)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	render_sectors(app);
	render_ui_frame(app, (t_rect){320, 132, 224, 64}, 1, DARK_GREY);
	change_font(app, 32, DARK_RED);
	render_text(app, (t_rect){336, 146, 800, 800}, "CONTROLS");
	render_ui_frame(app, (t_rect){320, 180, 640, 360}, 1, DARK_GREY);
	button_function(app,
		render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"),
		game_options);
	change_font(app, 16, CYAN);
	render_text(app, (t_rect){336, 196, 624, 16}, "MOVE            W,A,S,D");
	render_text(app, (t_rect){336, 220, 624, 16}, "JUMP            SPACEBAR");
	render_text(app, (t_rect){336, 244, 624, 16}, "INTERACT        F");
	render_text(app, (t_rect){336, 268, 624, 16}, "SHOOT           LEFT CLICK");
	render_text(app, (t_rect){336, 292, 624, 16}, "RELOAD          R");
	render_text(app, (t_rect){336, 316, 624, 16}, "MEDKIT          Q");
	render_text(app, (t_rect){336, 340, 624, 16}, "SHIELDS         E");
	render_text(app, (t_rect){336, 364, 624, 16}, "TOGGLE JETPACK  C");
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}
