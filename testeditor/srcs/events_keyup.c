/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_keyup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:15:51 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/13 14:11:01 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Events for WASD keys.
 * 
 * @param app
 * @param keycode
*/
static void	handle_wasd_keys(t_app *app, int keycode)
{
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
 * @brief Keyup events for different edit modes.
 * 
 * @param app
 * @param keycode
*/
static void	edit_mode_keys(t_app *app, int keycode)
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
	if (keycode == SDLK_g)
		app->decor_edit = ft_toggle(app->decor_edit);
	if (keycode == SDLK_e)
		app->var_edit = ft_toggle(app->var_edit);
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
 * @brief Handles events for key presses (keyup).
 * 
 * @param app
 * @param keycode
 * @return int
 */
int	events_keyup(t_app *app, int keycode)
{
	handle_wasd_keys(app, keycode);
	edit_mode_keys(app, keycode);
	if (keycode == SDLK_m)
		export_file(app, FILE_PATH);
	if (keycode == SDLK_o && !app->imported && !app->sectors)
		import_file(app, FILE_PATH);
	if (keycode == SDLK_i)
		link_interaction(app);
	if (keycode == SDLK_l)
		link_wall_to_sector(app);
	if (keycode == SDLK_DELETE && !app->current_object)
		sector_pop(app, &(app->active_sector), NULL);
	if (keycode == SDLK_DELETE && app->current_object)
		del_object(app, get_object_id(app, app->current_object));
	if (keycode == SDLK_y || keycode == SDLK_h)
		activate_slope(app, keycode);
	if (keycode == SDLK_x || keycode == SDLK_z)
		move_divider(app, keycode);
	if (keycode == SDLK_ESCAPE)
		exit(EXIT_SUCCESS);
	if (keycode == SDLK_LSHIFT)
		app->keystates ^= SHIFT_DOWN;
	return (0);
}

/**
 * @brief Handles map navigation.
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
