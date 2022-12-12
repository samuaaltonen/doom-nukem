/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/12 14:10:17 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	export_to_array(t_app *app, t_exportsector *export, int sectorid)
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
static void	import_floor_slope(t_exportsector *export, t_sector *sector)
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
static void	import_ceil_slope(t_exportsector *export, t_sector *sector)
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
static void read_sector(t_app *app, t_exportsector *export, int sectorid, int sector_count)
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
	app->player.current_sector = player->sector;
	app->player.pos = player->position;
	app->player.hp = player->health;
	app->player.weapons = player->weapons;
	app->player.shield = player->armor;
	ft_memcpy(&app->player.inventory, &player->inventory, sizeof(t_inventory));

}

static void relink_player(t_app *app, t_export_player *player)
{
	(void)player;
	app->player.elevation = app->sectors[app->player.current_sector].floor_height;
}

//open a file
int	import_file(t_app *app, char *path)
{
	int						fd;
	t_exportsector			*export;
	int						counter = 0;
	t_sector				*sectors;
	t_export_player			player;

	fd = open(path, O_RDONLY, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	if (read(fd, &app->conf->header,(sizeof(t_level_header))) == -1)
		exit_error(MSG_ERROR_FILE_READ);
	if (read(fd, &player, sizeof(t_export_player)) == -1)
		exit_error("player read error\n");
	import_player(app, &player);
	sectors = (t_sector *)ft_memalloc(sizeof(t_sector) * app->conf->header.sector_count); 
	app->sectors = sectors;
	while(counter < app->conf->header.sector_count)
	{
		if (read(fd, export,sizeof(t_exportsector)) == -1)
			exit_error(MSG_ERROR_FILE_READ);
		read_sector(app, export, counter, app->conf->header.sector_count);
		counter++;
	}
	free(export);
	if (read(fd, app->objects, sizeof(t_object) * MAX_OBJECTS) ==  -1)
		exit_error("Object read error\n");
	if (read(fd, app->interactions, sizeof(t_interaction) * MAX_INTERACTIONS) == -1)
		exit_error("Interaction read error\n");
	relink_player(app, &player);
	ft_printf("sector_count=%i\n",app->conf->header.sector_count);
	close(fd);
	return (0);
}