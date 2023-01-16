/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 19:28:23 by saaltone         ###   ########.fr       */
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

/**
 * @brief Imports objects.
 * 
 * @param app 
 * @param info 
 */
void	import_objects(t_app *app, t_import_info *info)
{
	t_export_object	objects[MAX_OBJECTS];
	t_object		temp;
	int				i;

	if (sizeof(t_export_object) * MAX_OBJECTS
		> (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_OBJECT);
	ft_memcpy(&objects, info->data + info->imported,
		sizeof(t_export_object) * MAX_OBJECTS);
	info->imported += (int) sizeof(t_export_object) * MAX_OBJECTS;
	i = -1;
	while (++i < MAX_OBJECTS)
	{
		temp.position = objects[i].pos;
		if (objects[i].sector < 0 || objects[i].sector >= app->sector_count)
			exit_error(MSG_ERROR_IMPORT_OBJECT);
		temp.sector = sector_by_index(app, objects[i].sector);
		temp.type = objects[i].type;
		if (!temp.sector || temp.type < 0 || temp.type > MAX_SMALL_OBJECTS
			+ MAX_BIG_OBJECTS + MAX_ENEMY_TYPES)
			exit_error(MSG_ERROR_IMPORT_OBJECT);
		temp.var = objects[i].var;
		(app->objects[i]) = temp;
	}
}

/**
 * @brief Relinks the pointer references of sectors using integer values in
 * saved file.
 * 
 * @param app 
 */
static void	relink_sectors(t_app *app)
{
	int				i;
	t_sector_lst	*head;

	head = app->sectors;
	while (head)
	{
		i = 0;
		while (i < MAX_MEMBER_SECTORS)
		{
			if (head->member_links[i] != -1)
			{
				head->member_sectors[i] = sector_by_index(app,
						head->member_links[i]);
				if (!head->member_sectors[i] || head->member_sectors[i] == head)
					exit_error(MSG_ERROR_IMPORT_SECTOR);
				head->member_sectors[i]->parent_sector = head;
			}
			else
				head->member_sectors[i] = NULL;
			i++;
		}
		head = head->next;
	}
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
static void	import_set_complete(t_import_info *info)
{
	if (pthread_mutex_lock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	((t_app *)info->thread->app)->import_progress = 1.0;
	if (pthread_mutex_unlock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
void	uncompression_update_progress(t_import_info *info)
{
	static int	last_update;

	if (info->uncompressed - last_update > MIN_UNCOMPRESS_UPDATE
		|| info->uncompressed == info->compressed_length)
	{
		if (pthread_mutex_lock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		if (info->compressed_length > 0)
			((t_app *)info->thread->app)->import_progress
				= (double) info->uncompressed
					/ (double) (info->compressed_length - 1);
		if (pthread_mutex_unlock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		last_update = info->uncompressed;
	}
}

/**
 * @brief Opens a file from the given path
 * 	reads all sector data into the sector list
 * 
 * @param app 
 * @param path 
 * @return int 
 */
int	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_import_info	info;

	info.data = NULL;
	info.thread = thread;
	rle_uncompress_data(&info, path, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) > (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	app->interaction_count = 0;
	app->object_count = info.header.object_count;
	import_sectors(app, &info);
	import_player(app, &info);
	import_objects(app, &info);
	import_interactions(app, &info);
	relink_sectors(app);
	app->imported = TRUE;
	free(info.data);
	import_set_complete(&info);
	return (0);
}
