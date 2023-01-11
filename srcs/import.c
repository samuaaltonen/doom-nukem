/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/11 14:32:52 by saaltone         ###   ########.fr       */
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
static int import_player(t_app *app, unsigned char *data, int available)
{
	t_export_player		player;

	if (sizeof(t_export_player) >= (size_t)available)
		exit_error(MSG_ERROR_IMPORT_PLAYER);
	ft_memcpy(&player, data, sizeof(t_export_player));
	app->player.sector = player.sector;
	app->player.pos = player.position;
	app->player.hp = player.health;
	app->player.weapons = player.weapons;
	app->player.shield = player.armor;
	app->player.elevation = sector_floor_height(app, app->player.sector,
		app->player.pos);
	ft_memcpy(&app->player.inventory, &player.inventory, sizeof(t_inventory));
	return ((int)sizeof(t_export_player));
}

static t_bool import_objects(t_app *app, unsigned char *data, int *imported)
{
	t_object	import;
	int			i;

	i = -1;
	while(++i < MAX_OBJECTS)
	{
		ft_memcpy(&import, data + *imported, sizeof(t_object));
		*imported += sizeof(t_object);
		app->objects[i].elevation = import.elevation;
		app->objects[i].position = import.position;
		app->objects[i].sector = import.sector;
		app->objects[i].type = import.type;
		app->objects[i].var = import.var;
		app->objects[i].rot = 0.f;
	}
	return (TRUE);
}

/**
 * @brief Imports surface pixel data.
 * 
 * @param info 
 * @param data 
 * @param imported 
 * @return SDL_Surface* 
 */
SDL_Surface	*import_surface(t_export_asset info, unsigned char *data,
	int *imported)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurface(0, info.width, info.height,
			IMAGE_PIXEL_BITS, 0, 0, 0, 0);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	ft_memcpy(surface->pixels, data + *imported, info.size);
	*imported += info.size;
	return (surface);
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
static void	update_progress(t_app *app, t_thread_data *thread, double progress)
{
	if (pthread_mutex_lock(&thread->lock))
		exit_error(NULL);
	app->import_progress = progress;
	if (pthread_mutex_unlock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_SIGNAL);
}

void	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_level_header		header;

	unsigned char	*data;
	int				length;
	int				imported;

	data = NULL;
	rle_uncompress_data(path, &data, &length);
	if (!data)
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&header, data, sizeof(t_level_header));
	imported = sizeof(t_level_header);
	update_progress(app, thread, (double) imported / (double) length);
	imported += import_sectors(app, header, data + imported, length - imported);
	update_progress(app, thread, (double) imported / (double) length);
	
	imported += import_player(app, data + imported, length - imported);
	update_progress(app, thread, (double) imported / (double) length);

	import_objects(app, data, &imported);

	ft_memcpy(app->interactions, data + imported, sizeof(t_interaction) * MAX_INTERACTIONS);
	imported += sizeof(t_interaction) * MAX_INTERACTIONS;
	update_progress(app, thread, (double) imported / (double) length);

	app->assets.sprite = import_surface(header.asset_info[EXPORT_PANELS], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.bg = import_surface(header.asset_info[EXPORT_SKYBOX], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.font.font = import_surface(header.asset_info[EXPORT_FONT], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.ui_frame = import_surface(header.asset_info[EXPORT_UI_FRAME], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.title_screen_image = import_surface(header.asset_info[EXPORT_TITLESCREEN], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.crosshair = import_surface(header.asset_info[EXPORT_CROSSHAIR], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.pointer = import_surface(header.asset_info[EXPORT_POINTER], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.shield = import_surface(header.asset_info[EXPORT_SHIELD], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.hp = import_surface(header.asset_info[EXPORT_HP], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.pistol = import_surface(header.asset_info[EXPORT_PISTOL], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.bullet = import_surface(header.asset_info[EXPORT_BULLET], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.meter = import_surface(header.asset_info[EXPORT_METER], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);

	SDL_Surface *temp = import_surface(header.asset_info[EXPORT_OBJECT_ICON], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	SDL_FreeSurface(temp);

	app->assets.weapon = import_surface(header.asset_info[EXPORT_WEAPON_HD], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);

	app->assets.sprites[SMALL_SPRITE] = import_surface(header.asset_info[EXPORT_PICKUP], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[BIG_SPRITE] = import_surface(header.asset_info[EXPORT_OBJECT], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[PROJECTILE_SPRITE] = import_surface(header.asset_info[EXPORT_SPRITE], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[ENEMY_SPRITE_1] = import_surface(header.asset_info[EXPORT_MONSTER_1], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[ENEMY_SPRITE_2] = import_surface(header.asset_info[EXPORT_MONSTER_2], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);

	/* import_wav(app, header.asset_info[EXPORT_MUSIC], data, &imported);
	import_wav(app, header.asset_info[EXPORT_SOUND_LASER], data, &imported);
	import_wav(app, header.asset_info[EXPORT_SOUND_SHOT], data, &imported);
	import_wav(app, header.asset_info[EXPORT_SOUND_RELOAD], data, &imported);
	import_wav(app, header.asset_info[EXPORT_SOUND_BUMP], data, &imported);
	import_text(app, header.asset_info[EXPORT_TEXTS], data, &imported); */
	update_progress(app, thread, 1.0);
	free(data);
}
