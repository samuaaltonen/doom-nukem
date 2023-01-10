/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/10 17:42:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	export_to_array(t_app *app, t_export_sector *export, int sectorid)
{
	ft_memcpy(app->sectors[sectorid].corners, export->corners, export->corner_count * sizeof(t_vector2));
	ft_memcpy(app->sectors[sectorid].wall_textures, export->wall_textures, export->corner_count * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_types, export->wall_types, export->corner_count *  sizeof(int));
	ft_memcpy(app->sectors[sectorid].member_sectors, export->member_sectors, MAX_MEMBER_SECTORS * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_decor, export->wall_decor, sizeof(export->wall_decor));
	ft_memcpy(app->sectors[sectorid].decor_offset, export->decor_offset, sizeof(export->decor_offset));
}

/**
 * @brief Modifies slope ending coordinates so that slope is always
 * perpendicular to the starting wall. Returns modified ending coordinate.
 * 
 * @param sector 
 * @param start 
 * @param end 
 * @return t_vector2 
 */
static t_vector2	slope_perpendicular(t_sector *sector, int start, int end)
{
	t_vector2	slope;
	t_vector2	start_wall;
	t_vector2	perpendicular;
	double		perpendicular_distance;

	slope = ft_vector2_sub(sector->corners[end], sector->corners[start]);
	if (start < sector->corner_count - 1)
		start_wall = ft_vector2_sub(sector->corners[start + 1], sector->corners[start]);
	else
		start_wall = ft_vector2_sub(sector->corners[0], sector->corners[start]);
	perpendicular = ft_vector_resize(ft_vector_perpendicular(start_wall), 1.0);
	perpendicular_distance = ft_vector_length(slope) * fabs(cos(ft_vector_angle(slope, perpendicular)));
	return ((t_vector2){
		sector->corners[start].x + perpendicular_distance * perpendicular.x,
		sector->corners[start].y + perpendicular_distance * perpendicular.y
	});
}

/**
 * @brief reads imported sector slop points, calculates the slope angles from the points
 * 	angles.y = angle rotation to world direction
 * 	angles.x = floor angle
 * 
 * @param app 
 * @param export 
 * @param sector 
 */
static void	import_floor_slope(t_export_sector *export, t_sector *sector)
{
	t_vector2	point;

	if (export->floor_slope_position == -1)
		return ;
	point = sector->corners[export->floor_slope_position];
	sector->floor_slope_height = export->floor_slope_height - export->floor_height;
	if (!sector->floor_slope_height)
		return ;
	sector->floor_slope_start = point;
	sector->floor_slope_end = slope_perpendicular(sector,
		export->floor_slope_position,
		export->floor_slope_opposite);
	sector->floor_slope_magnitude = sector->floor_slope_height 
		/ ft_vector_length(ft_vector2_sub(sector->floor_slope_end,
			sector->floor_slope_start));
}

/**
 * @brief reads imported sector slop points,
 * calculates the slope angles from the points
 * 	angles.y = angle rotation to world direction
 * 	angles.x = floor angle
 * 
 * @param app 
 * @param export 
 * @param sector 
 */
static void	import_ceil_slope(t_export_sector *export, t_sector *sector)
{
	t_vector2	point;

	if (export->ceil_slope_position == -1)
		return ;
	point = sector->corners[export->ceil_slope_position];
	sector->ceil_slope_height = export->ceil_slope_height - export->ceil_height;
	if (!sector->ceil_slope_height)
		return ;
	sector->ceil_slope_start = point;
	sector->ceil_slope_end = slope_perpendicular(sector,
		export->ceil_slope_position,
		export->ceil_slope_opposite);
	sector->ceil_slope_magnitude = sector->ceil_slope_height 
		/ ft_vector_length(ft_vector2_sub(sector->ceil_slope_end,
			sector->ceil_slope_start));
}

//read sector data from export
static void read_sector(t_app *app, t_export_sector *export, int sectorid, int sector_count)
{
	(void)sector_count;
	app->sectors[sectorid].corner_count = export->corner_count;
	export_to_array(app, export, sectorid);
	app->sectors[sectorid].light = (double)export->light;
	app->sectors[sectorid].ceil_texture = export->ceil_tex;
	app->sectors[sectorid].ceil_tex_offset = export->ceil_tex_offset;
	app->sectors[sectorid].floor_texture = export->floor_tex;
	app->sectors[sectorid].floor_tex_offset = export->floor_tex_offset;
	app->sectors[sectorid].ceil_height = export->ceil_height;
	app->sectors[sectorid].floor_height = export->floor_height;
	app->sectors[sectorid].parent_sector = export->parent_sector;
	app->sectors[sectorid].floor_slope_height = 0.0;
	app->sectors[sectorid].ceil_slope_height = 0.0;
	import_floor_slope(export, &(app->sectors[sectorid]));
	import_ceil_slope(export, &(app->sectors[sectorid]));
}

static void import_player(t_app *app, t_export_player *player)
{
	app->player.sector = player->sector;
	app->player.pos = player->position;
	app->player.hp = player->health;
	app->player.weapons = player->weapons;
	app->player.shield = player->armor;
	ft_memcpy(&app->player.inventory, &player->inventory, sizeof(t_inventory));
}

static void relink_player(t_app *app, t_export_player *player)
{
	(void)player;
	app->player.elevation = sector_floor_height(app, app->player.sector, app->player.pos);
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

//open a file
/* int	import_file(t_app *app, char *path)
{
	int						fd;
	t_export_sector			*export;
	int						counter = 0;
	t_sector				*sectors;
	t_export_player			player;
	t_level_header			header;

	fd = open(path, O_RDONLY, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	export = (t_export_sector *)ft_memalloc(sizeof(t_export_sector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	if (read(fd, &header,(sizeof(t_level_header))) == -1)
		exit_error(MSG_ERROR_FILE_READ);
	sectors = (t_sector *)ft_memalloc(sizeof(t_sector) * header.sector_count); 
	app->sectors = sectors;
	while(counter < header.sector_count)
	{
		if (read(fd, export,sizeof(t_export_sector)) == -1)
			exit_error(MSG_ERROR_FILE_READ);
		read_sector(app, export, counter, header.sector_count);
		counter++;
	}
	free(export);
	if (read(fd, &player, sizeof(t_export_player)) == -1)
		exit_error("player read error\n");
	import_player(app, &player);
	import_objects(app, fd);
	if (read(fd, app->interactions, sizeof(t_interaction) * MAX_INTERACTIONS) == -1)
		exit_error("Interaction read error\n");
	relink_player(app, &player);
	ft_printf("sector_count=%i\n",header.sector_count);
	close(fd);
	return (0);
} */

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

static void	update_progress(t_app *app, t_thread_data *thread, double progress)
{
	if (pthread_mutex_lock(&thread->lock))
		exit_error(NULL);
	app->import_progress = progress;
	ft_printf("%f\n", app->import_progress);
	if (pthread_mutex_unlock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_SIGNAL);
}

void	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_export_sector			*export;
	int						counter = 0;
	t_export_player			player;
	t_level_header			header;

	unsigned char	*data;
	int				length;
	int				imported;

	data = NULL;
	rle_uncompress_data(path, &data, &length);
	ft_memcpy(&header, data, sizeof(t_level_header));
	imported = sizeof(t_level_header);
	update_progress(app, thread, (double) imported / (double) length);
	export = (t_export_sector *)ft_memalloc(sizeof(t_export_sector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	app->sectors = (t_sector *)ft_memalloc(sizeof(t_sector) * header.sector_count);
	while (counter < header.sector_count)
	{
		ft_memcpy(export, data + imported, sizeof(t_export_sector));
		imported += sizeof(t_export_sector);
		update_progress(app, thread, (double) imported / (double) length);
		read_sector(app, export, counter, header.sector_count);
		counter++;
	}
	free(export);
	ft_memcpy(&player, data + imported, sizeof(t_export_player));
	imported += sizeof(t_export_player);
	update_progress(app, thread, (double) imported / (double) length);
	import_player(app, &player);
	import_objects(app, data, &imported);
	ft_memcpy(app->interactions, data + imported, sizeof(t_interaction) * MAX_INTERACTIONS);
	imported += sizeof(t_interaction) * MAX_INTERACTIONS;
	update_progress(app, thread, (double) imported / (double) length);
	relink_player(app, &player);

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
	app->assets.sprites[0] = import_surface(header.asset_info[EXPORT_PICKUP], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[1] = import_surface(header.asset_info[EXPORT_OBJECT], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	import_surface(header.asset_info[EXPORT_OBJECT_ICON], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[3] = import_surface(header.asset_info[EXPORT_MONSTER_1], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[4] = import_surface(header.asset_info[EXPORT_MONSTER_2], data, &imported);
	update_progress(app, thread, (double) imported / (double) length);
	app->assets.sprites[2] = import_surface(header.asset_info[EXPORT_SPRITE], data, &imported);
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
