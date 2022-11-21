/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/21 13:41:57 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Keyup events for WASD and arrow keys.
*/
static void	wasd_and_arrow_keys(int keycode, t_app *app)
{

	if (keycode == SDLK_RIGHT)
		sector_edit(app, keycode);
	if (keycode == SDLK_LEFT)
		sector_edit(app, keycode);
	if (keycode == SDLK_UP)
		sector_edit(app, keycode);
	if (keycode == SDLK_DOWN)
		sector_edit(app, keycode);
	if (keycode == SDLK_w)
		app->keystates ^= FORWARD_W_DOWN;
	if (keycode == SDLK_s)
		app->keystates ^= BACKWARD_S_DOWN;
	if (keycode == SDLK_a)
		app->keystates ^= LEFT_DOWN;
	if (keycode == SDLK_d)
		app->keystates ^= RIGHT_DOWN;
}

/**
 * Keyup events for different edit modes.
*/
static void	edit_mode_keys(int keycode, t_app *app)
{
	if (keycode == SDLK_p)
		app->player_edit = ft_toggle(app->player_edit);
	if (keycode == SDLK_r)
		app->ceiling_edit = ft_toggle(app->ceiling_edit);
	if (keycode == SDLK_f)
		app->floor_edit = ft_toggle(app->floor_edit);
	if (keycode == SDLK_t)
		app->light_edit = ft_toggle(app->light_edit);
	if (keycode == SDLK_u)
		app->slope_edit = ft_toggle(app->slope_edit);
	if (keycode == SDLK_v)
		app->wall_edit = ft_toggle(app->wall_edit);
	if (keycode == SDLK_n)
		toggle_new_object(app, app->object_new);
	if (keycode == SDLK_c)
	{
		app->list_creation = ft_toggle(app->list_creation);
		if (app->list_ongoing)
			cancel_list_creation(app);
	}
}

/**
 * Handles events for key presses (keyup).
 */
int	events_keyup(int keycode, t_app *app)
{
	wasd_and_arrow_keys(keycode, app);
	edit_mode_keys(keycode, app);
	if (keycode == SDLK_m)
		export_file(app, FILE_PATH);
	if (keycode == SDLK_o)
		import_file(app, FILE_PATH);
	if (keycode == SDLK_i)
		link_interaction(app);
	if (keycode == SDLK_l)
		link_wall_to_sector(app);
	if (keycode == SDLK_DELETE)
		sector_pop(app, &(app->active_sector), NULL);
	if (keycode == SDLK_y || keycode == SDLK_h)
		activate_slope(app, keycode);
	if (keycode == SDLK_x || keycode == SDLK_z)
		move_divider(app, keycode);
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
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
		app->view_pos.y += MAP_SPEED / app->movement_speed;
	if (app->keystates & BACKWARD_DOWN
		|| app->keystates & BACKWARD_S_DOWN)
		app->view_pos.y -= MAP_SPEED / app->movement_speed;
	if (app->keystates & LEFT_DOWN)
		app->view_pos.x -= MAP_SPEED / app->movement_speed;
	if (app->keystates & RIGHT_DOWN)
		app->view_pos.x += MAP_SPEED / app->movement_speed;
}
