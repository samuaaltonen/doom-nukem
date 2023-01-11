/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/11 20:37:31 by saaltone         ###   ########.fr       */
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
	app->player.sector = sector_by_index(app, player.sector);
	app->player.health = player.health;
	from_bits(app, player.weapons, app->player.weapons);
	app->player.inventory = player.inventory;
	app->player.sector = sector_by_index(app, player.sector);
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
	i = 0;
	while (i < MAX_OBJECTS)
	{
		temp.position = objects[i].pos;
		temp.sector = sector_by_index(app, objects[i].sector);
		temp.type = objects[i].type;
		temp.var = objects[i].var;
		(app->objects[i]) = temp;
		i++;
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
 * @brief Opens a file from the given path
 * 	reads all sector data into the sector list
 * 
 * @param app 
 * @param path 
 * @return int 
 */
int	import_file(t_app *app, char *path)
{
	t_import_info	info;

	info.data = NULL;
	rle_uncompress_data(path, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) > (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	app->interaction_count = info.header.interaction_count;
	app->object_count = info.header.object_count;
	import_sectors(app, &info);
	import_player(app, &info);
	import_objects(app, &info);
	import_interactions(app, &info);
	relink_sectors(app);
	app->imported = TRUE;
	free(info.data);
	return (0);
}
