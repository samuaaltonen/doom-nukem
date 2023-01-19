/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_pausemenu.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 16:55:41 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Renders pausemenu.
 * 
 * @param app 
 */
void	render_pausemenu(t_app *app)
{	
	SDL_SetRelativeMouseMode(SDL_FALSE);
	render_sectors(app);
	render_ui_frame(app, (t_rect){28, 78, 300, 428}, 1, DARK_GREY);
	button_function(app,
		render_button(app, (t_rect){50, 100, 256, 64}, 1, "MAIN MENU"),
		main_menu);
	button_function(app,
		render_button(app, (t_rect){50, 180, 256, 64}, 1, "CONTINUE"),
		pause_game);
	button_function(app,
		render_button(app, (t_rect){50, 260, 256, 64}, 1, "LEVEL EDITOR"),
		do_nothing);
	button_function(app,
		render_button(app, (t_rect){50, 340, 256, 64}, 1, "OPTIONS"),
		game_options);
	button_function(app,
		render_button(app, (t_rect){50, 420, 256, 64}, 1, "QUIT GAME"),
		exit_game);
	render_ui(app);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}
