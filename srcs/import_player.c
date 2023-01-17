/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:17:25 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 14:18:01 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
	app->player.hp = player.health;
	app->player.weapons = player.weapons;
	app->player.shield = player.armor;
	if (player.sector < 0 || player.sector >= app->sector_count)
		exit_error(MSG_ERROR_VALIDATION_PLAYER);
	app->player.elevation = sector_floor_height(app, app->player.sector,
			app->player.pos);
	ft_memcpy(&app->player.inventory, &player.inventory, sizeof(t_inventory));
	info->imported += (int) sizeof(t_export_player);
	import_update_progress(info);
}
