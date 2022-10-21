/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/21 14:33:54 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Handles events for key presses (keyup).
 */
int	events_keyup(int keycode, t_app *app)
{
	if (keycode == SDLK_RIGHT)
		sector_edit(app, keycode);
	if (keycode == SDLK_LEFT)
		sector_edit(app, keycode);
	if (keycode == SDLK_UP)
		sector_edit(app, keycode);
	if (keycode == SDLK_DOWN)
		sector_edit(app, keycode);
	if (keycode == SDLK_u)
		sector_edit(app, keycode);
	if (keycode == SDLK_j)
		sector_edit(app, keycode);
	if (keycode == SDLK_w)
		app->keystates ^= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates ^= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates ^= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates ^= RIGHT_DOWN;
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	if (keycode == SDLK_h)
		app->toggle_help = ft_toggle(app->toggle_help);
	if (keycode == SDLK_c)
		app->list_creation = ft_toggle(app->list_creation);
	if (keycode == SDLK_m)
		export_file(app, FILE_PATH);
	if (keycode == SDLK_o)
		import_file(app, FILE_PATH);
	if(keycode == SDLK_DELETE)
		sector_pop(app, &(app->active_sector), NULL);
	if(keycode == SDLK_l)
		link_wall_to_sector(app);
	if(keycode == SDLK_r)
		app->ceiling_edit = ft_toggle(app->ceiling_edit);
	if(keycode == SDLK_f)
		app->floor_edit = ft_toggle(app->floor_edit);
	if(keycode == SDLK_t)
		app->light_edit = ft_toggle(app->light_edit);
	if(app->active_sector && app->active && keycode == SDLK_y)
	{
		app->active_sector->ceil_slope_wall = app->active;
		app->active_sector->ceil_slope_opposite = find_opposite_point(app->active_sector, app->active);
	}
	if(app->active_sector && app->active && keycode == SDLK_h)
	{
		app->active_sector->floor_slope_wall = app->active;
		app->active_sector->floor_slope_opposite = find_opposite_point(app->active_sector, app->active);
	}

	//temp
	if (keycode == SDLK_0)
		change_selected_wall_tex(app, app->active, 0);
	if (keycode == SDLK_1)
		change_selected_wall_tex(app, app->active, 1);
	if (keycode == SDLK_2)
		change_selected_wall_tex(app, app->active, 2);
	if (keycode == SDLK_3)
		change_selected_wall_tex(app, app->active, 3);
	if (keycode == SDLK_4)
		change_selected_wall_tex(app, app->active, 4);
	if (keycode == SDLK_5)
		change_selected_wall_tex(app, app->active, 5);
	if (keycode == SDLK_6)
		change_selected_wall_tex(app, app->active, 6);
	if (keycode == SDLK_7)
		change_selected_wall_tex(app, app->active, 7);
	if (keycode == SDLK_8)
		change_selected_wall_tex(app, app->active, 8);
	if (keycode == SDLK_9)
		change_selected_wall_tex(app, app->active, 9);
	return (0);
}

/**
 * Handles events for key presses (keydown).
 */
int	events_keydown(int keycode, t_app *app)
{
	if (keycode == SDLK_w)
		app->keystates |= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates |= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates |= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates |= RIGHT_DOWN;
	return (0);
}

/**
 * @brief handle map navigation
 * 
 * @param app 
 */
void	handle_movement(t_app *app)
{
	if (app->keystates & FORWARD_DOWN
		|| app->keystates & FORWARD_W_DOWN)
		app->view_pos.y += MAP_SPEED;
	if (app->keystates & BACKWARD_DOWN
		|| app->keystates & BACKWARD_S_DOWN)
		app->view_pos.y -= MAP_SPEED;
	if (app->keystates & LEFT_DOWN)
		app->view_pos.x -= MAP_SPEED;
	if (app->keystates & RIGHT_DOWN)
		app->view_pos.x += MAP_SPEED;
}