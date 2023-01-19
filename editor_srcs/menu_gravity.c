/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_gravity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:51:13 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 18:51:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Handles main menu button clicks.
 * 
 * @param app 
 * @param mouse 
 */
static void	main_menu_events(t_app *app)
{
	t_point		mouse;

	if (!app->mouse_down
		|| app->active_sector
		|| app->active
		|| app->interaction_menu
		|| app->object_menu
		|| app->player_menu)
		return ;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (check_mouse(mouse, (t_rect){160, 300, 30, 20}))
		app->gravity -= 0.02;
	if (check_mouse(mouse, (t_rect){240, 300, 30, 20}))
		app->gravity += 0.02;
	if (app->gravity > MAX_GRAVITY)
		app->gravity = MAX_GRAVITY;
	if (app->gravity < MIN_GRAVITY)
		app->gravity = MIN_GRAVITY;
}

/**
 * @brief Renders gravity select buttons and value.
 * 
 * @param app 
 */
void	gravity_menu(t_app *app)
{
	t_point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (check_mouse(mouse, (t_rect){160, 300, 30, 20}))
		color_surface(app->assets.ui_frame, ACTIVE_TEXT);
	else
		color_surface(app->assets.ui_frame, TEXT);
	render_ui_frame(app, (t_rect){160, 300, 30, 20}, 1, BG_MENU);
	if (check_mouse(mouse, (t_rect){240, 300, 30, 20}))
		color_surface(app->assets.ui_frame, ACTIVE_TEXT);
	else
		color_surface(app->assets.ui_frame, TEXT);
	render_ui_frame(app, (t_rect){240, 300, 30, 20}, 1, BG_MENU);
	render_text(app, (t_rect){18, 305, 270, 15}, "GRAVITY");
	render_amount_info(app, (t_rect){205, 305, 90, 15}, (int)app->gravity);
	render_text(app, (t_rect){174, 303, 15, 15}, "<");
	render_text(app, (t_rect){254, 303, 15, 15}, ">");
	main_menu_events(app);
}
