/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:17:25 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/21 14:23:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Zeroes player movement and resets its direction.
 * 
 * @param app 
 */
static void	reset_player_data(t_app *app)
{
	app->player.dir = (t_vector2){DIRECTION_START_X, DIRECTION_START_Y};
	app->player.elevation_velocity = 0.0;
	app->player.height = PLAYER_HEIGHT_STANDING;
	init_camera_plane(app);
	init_skybox_plane(app);
	app->player.move_vector = (t_vector2){0.0, 0.0};
	app->player.move_pos = app->player.pos;
	app->player.flying = FALSE;
	app->player.jetpack = FALSE;
	app->player.inventory.energy = PLAYER_MAX_ENERGY;
	app->player.is_decelerating = TRUE;
}

/**
 * @brief Imports player data.
 * 
 * @param app 
 * @param data 
 * @param available 
 * @return int 
 */
void	import_player(t_app *app, t_import_info *info)
{
	t_export_player		player;

	if (sizeof(t_export_player) >= (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_PLAYER);
	ft_memcpy(&player, info->data + info->imported, sizeof(t_export_player));
	app->player.sector = player.sector;
	app->player.pos = player.position;
	if (!app->assets_imported || app->player.hp <= 0)
	{
		app->player.hp = player.health;
		app->player.weapons = player.weapons;
		app->player.shield = player.armor;
		ft_memcpy(&app->player.inventory, &player.inventory,
			sizeof(t_inventory));
	}
	if (player.sector < 0 || player.sector >= app->sector_count)
		exit_error(MSG_ERROR_VALIDATION_PLAYER);
	app->player.elevation = sector_floor_height(app, app->player.sector,
			app->player.pos);
	info->imported += (int) sizeof(t_export_player);
	import_update_progress(info);
	if (app->assets_imported)
		reset_player_data(app);
}
