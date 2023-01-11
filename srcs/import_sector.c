/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:06:54 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 17:51:21 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
		start_wall = ft_vector2_sub(sector->corners[start + 1],
				sector->corners[start]);
	else
		start_wall = ft_vector2_sub(sector->corners[0], sector->corners[start]);
	perpendicular = ft_vector_resize(ft_vector_perpendicular(start_wall), 1.0);
	perpendicular_distance = ft_vector_length(slope) * fabs(cos(
				ft_vector_angle(slope, perpendicular)));
	return ((t_vector2){
		sector->corners[start].x + perpendicular_distance * perpendicular.x,
		sector->corners[start].y + perpendicular_distance * perpendicular.y
	});
}

/**
 * @brief Calculates sector's floor slope values.
 * 
 * @param export 
 * @param sector 
 */
static void	import_floor_slope(t_export_sector *export, t_sector *sector)
{
	t_vector2	point;

	if (export->floor_slope_position == -1)
		return ;
	point = sector->corners[export->floor_slope_position];
	sector->floor_slope_height = export->floor_slope_height
		- export->floor_height;
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
 * @brief Calculates sector's ceiling slope values.
 * 
 * @param export 
 * @param sector 
 */
static void	import_ceil_slope(t_export_sector *export, t_sector *sector)
{
	t_vector2	point;

	if (export->ceil_slope_position == -1)
		return ;
	point = sector->corners[export->ceil_slope_position];
	sector->ceil_slope_height = export->ceil_slope_height
		- export->ceil_height;
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

/**
 * @brief Copies sector data into main array.
 * 
 * @param app 
 * @param export 
 * @param sectorid 
 */
static void	read_sector(t_app *app, t_export_sector *export, int sectorid)
{
	app->sectors[sectorid].corner_count = export->corner_count;
	ft_memcpy(app->sectors[sectorid].corners, export->corners,
		export->corner_count * sizeof(t_vector2));
	ft_memcpy(app->sectors[sectorid].wall_textures, export->wall_textures,
		export->corner_count * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_types, export->wall_types,
		export->corner_count * sizeof(int));
	ft_memcpy(app->sectors[sectorid].member_sectors, export->member_sectors,
		MAX_MEMBER_SECTORS * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_decor, export->wall_decor,
		sizeof(export->wall_decor));
	ft_memcpy(app->sectors[sectorid].decor_offset, export->decor_offset,
		sizeof(export->decor_offset));
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

/**
 * @brief Allocates space and imports sector data to main sector array.
 * 
 * @param app 
 * @param header 
 * @param data 
 * @param available 
 * @return int 
 */
void	import_sectors(t_app *app, t_thread_data *thread, t_import_info *info)
{
	t_export_sector	export;
	int				counter;

	if (sizeof(t_sector) * info->header.sector_count
		>= (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_SECTOR);
	app->sectors = (t_sector *)ft_memalloc(sizeof(t_sector)
			* info->header.sector_count);
	if (!app->sectors)
		exit_error(MSG_ERROR_ALLOC);
	counter = 0;
	while (counter < info->header.sector_count)
	{
		ft_memcpy(&export, info->data + info->imported,
			sizeof(t_export_sector));
		info->imported += (int) sizeof(t_export_sector);
		read_sector(app, &export, counter);
		counter++;
	}
	import_update_progress(app, thread, info);
}
