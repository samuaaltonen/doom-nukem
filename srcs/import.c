/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/11 18:45:06 by saaltone         ###   ########.fr       */
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
static void	import_player(t_app *app, t_thread_data *thread,
	t_import_info *info)
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
	app->player.elevation = sector_floor_height(app, app->player.sector,
			app->player.pos);
	ft_memcpy(&app->player.inventory, &player.inventory, sizeof(t_inventory));
	info->imported += (int) sizeof(t_export_player);
	import_update_progress(app, thread, info);
}

/**
 * @brief Imports object data.
 * 
 * @param app 
 * @param data 
 * @param available 
 * @return int 
 */
static void	import_objects(t_app *app, t_thread_data *thread,
	t_import_info *info)
{
	t_object	import;
	int			i;

	if (sizeof(t_object) * MAX_OBJECTS
		>= (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_OBJECT);
	i = -1;
	while (++i < MAX_OBJECTS)
	{
		ft_memcpy(&import, info->data + info->imported, sizeof(t_object));
		info->imported += sizeof(t_object);
		app->objects[i].elevation = import.elevation;
		app->objects[i].position = import.position;
		app->objects[i].sector = import.sector;
		app->objects[i].type = import.type;
		app->objects[i].var = import.var;
		app->objects[i].rot = 0.f;
	}
	import_update_progress(app, thread, info);
}

/**
 * @brief Imports interaction data.
 * 
 * @param app 
 * @param data 
 * @param available 
 * @return int 
 */
static void	import_interactions(t_app *app, t_thread_data *thread,
	t_import_info *info)
{
	if (sizeof(t_interaction) * MAX_INTERACTIONS
		>= (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_INTERACTION);
	ft_memcpy(app->interactions, info->data + info->imported,
		sizeof(t_interaction) * MAX_INTERACTIONS);
	info->imported += (int) sizeof(t_interaction) * MAX_INTERACTIONS;
	import_update_progress(app, thread, info);
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
void	import_update_progress(t_app *app, t_thread_data *thread,
	t_import_info *info)
{
	if (pthread_mutex_lock(&thread->lock))
		exit_error(NULL);
	app->import_progress = (double) info->imported / (double) info->length;
	if (pthread_mutex_unlock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_SIGNAL);
}

/**
 * @brief Imports all data from level file.
 * 
 * @param app 
 * @param thread 
 * @param path 
 */
void	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_import_info		info;

	info.data = NULL;
	rle_uncompress_data(path, &info.data, &info.length);
	if (!info.data)
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	import_update_progress(app, thread, &info);
	import_sectors(app, thread, &info);
	import_player(app, thread, &info);
	import_objects(app, thread, &info);
	import_interactions(app, thread, &info);
	import_assets(app, thread, &info);
	info.imported = info.length;
	import_update_progress(app, thread, &info);
	free(info.data);
}
