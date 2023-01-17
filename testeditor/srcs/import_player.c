/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:31:04 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 19:31:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks weapon data by bits.
 * 
 * @param app 
 * @param export 
 * @param weapons 
 */
static void	from_bits(t_app *app, int export, t_weapon *weapons)
{
	int	i;

	i = 0;
	while (i < MAX_WEAPONS)
	{
		if (export & 1)
		{	
			weapons[i].enabled = TRUE;
			app->player.selected_weapon = i;
		}
		export >>= 1;
		i++;
	}
}

/**
 * @brief Imports player.
 * 
 * @param app 
 * @param info 
 */
void	import_player(t_app *app, t_import_info *info)
{
	t_export_player	player;

	if (sizeof(t_export_player) > (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_PLAYER);
	ft_memcpy(&player, info->data + info->imported, sizeof(t_export_player));
	info->imported += (int) sizeof(t_export_player);
	app->player_edit = FALSE;
	app->player_menu = FALSE;
	app->player.position = player.position;
	app->player.direction = player.direction;
	if (player.sector < 0 || player.sector >= app->sector_count)
		exit_error(MSG_ERROR_IMPORT_PLAYER);
	app->player.sector = sector_by_index(app, player.sector);
	if (!app->player.sector)
		exit_error(MSG_ERROR_IMPORT_PLAYER);
	app->player.health = player.health;
	from_bits(app, player.weapons, app->player.weapons);
	app->player.inventory = player.inventory;
}
