/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/01 13:58:00 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	export_to_array(t_app *app, t_exportsector *export, int sectorid)
{
	ft_memcpy(app->sectors[sectorid].corners, export->corners, export->corner_count * sizeof(t_vector2));
	ft_memcpy(app->sectors[sectorid].wall_textures, export->wall_textures, export->corner_count * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_types, export->wall_types, export->corner_count *  sizeof(int));
	ft_memcpy(app->sectors[sectorid].member_sectors, export->member_sectors, MAX_MEMBER_SECTORS * sizeof(int));
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
	t_vector2	linedst;
	t_vector2	opposite;

	if (export->floor_slope_position == -1)
		return ;
	point = sector->corners[export->floor_slope_position];
	if (export->floor_slope_position < sector->corner_count)
		linedst = sector->corners[export->floor_slope_position + 1];
	else
		linedst = sector->corners[0];
	opposite = (t_vector2){sector->corners[export->floor_slope_opposite].x,
			sector->corners[export->floor_slope_opposite].y};
	sector->floor_slope_position = (t_vector3){point.x, point.y,
			export->floor_slope_height};
	sector->floor_slope_angles.y = ft_vector_angle(
			ft_vector2_sub(linedst, point),(t_vector2){0.f,1.f});	
	ft_line_intersection(
			ft_line_resize((t_line){point, linedst}, MAX_LINE_LENGTH, 2),
			ft_line_resize((t_line){opposite, ft_vector2_add(
			ft_vector_perpendicular(ft_vector2_sub(linedst, point)), opposite)},
			MAX_LINE_LENGTH, 2),&point);
	sector->floor_slope_angles.x = atan(
			(export->floor_slope_height - export->floor_height) /
			ft_vector_length(ft_vector2_sub(opposite, point)));
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
	t_vector2	linedst;
	t_vector2	opposite;

	if (export->ceil_slope_position == -1)
		return ;
	point = sector->corners[export->ceil_slope_position];
	if (export->ceil_slope_position < sector->corner_count)
		linedst = sector->corners[export->ceil_slope_position + 1];
	else
		linedst = sector->corners[0];
	opposite = (t_vector2){sector->corners[export->ceil_slope_opposite].x,
			sector->corners[export->ceil_slope_opposite].y};
	sector->ceiling_slope_position = (t_vector3){point.x, point.y,
			export->ceil_slope_height};
	sector->ceiling_slope_angles.y = ft_vector_angle(
			ft_vector2_sub(linedst, point),(t_vector2){0.f,1.f});	
	ft_line_intersection(
			ft_line_resize((t_line){point, linedst}, MAX_LINE_LENGTH, 2),
			ft_line_resize((t_line){opposite, ft_vector2_add(
			ft_vector_perpendicular(ft_vector2_sub(linedst, point)), opposite)},
			MAX_LINE_LENGTH, 2),&point);
	sector->ceiling_slope_angles.x = atan(
			(export->ceil_slope_height - export->ceil_height) /
			ft_vector_length(ft_vector2_sub(opposite, point)));
}

//read sector data from export
static void read_sector(t_app *app, t_exportsector *export, int sectorid, int sector_count)
{
	(void)sector_count;
	app->sectors[sectorid].corner_count = export->corner_count;
	export_to_array(app, export, sectorid);
	app->sectors[sectorid].light = export->light;
	app->sectors[sectorid].ceiling_texture = export->ceil_tex;
	app->sectors[sectorid].ceil_tex_offset = export->ceil_tex_offset;
	app->sectors[sectorid].floor_texture = export->floor_tex;
	app->sectors[sectorid].floor_tex_offset = export->floor_tex_offset;
	app->sectors[sectorid].ceiling_height = export->ceil_height;
	app->sectors[sectorid].floor_height = export->floor_height;
	app->sectors[sectorid].parent_sector = export->parent_sector;

	app->sectors[sectorid].floor_slope_height = 0.0;
	app->sectors[sectorid].ceiling_slope_height = 0.0;
	/**
	 * TODO: REMOVE THIS
	 */
	if (sectorid == 13)
	{
		app->sectors[sectorid].floor_slope_height = 1.0;
		app->sectors[sectorid].floor_slope_end = (t_vector2){-2.0, 10.0};
		app->sectors[sectorid].floor_slope_start = (t_vector2){2.0, 10.0};
		app->sectors[sectorid].floor_slope_length = ft_vector_length(ft_vector2_sub(app->sectors[sectorid].floor_slope_end, app->sectors[sectorid].floor_slope_start));

		app->sectors[sectorid].ceiling_slope_height = -1.0;
		app->sectors[sectorid].ceiling_slope_end = (t_vector2){-2.0, 10.0};
		app->sectors[sectorid].ceiling_slope_start = (t_vector2){2.0, 10.0};
		app->sectors[sectorid].ceiling_slope_length = ft_vector_length(ft_vector2_sub(app->sectors[sectorid].ceiling_slope_end, app->sectors[sectorid].ceiling_slope_start));
	}
	import_floor_slope(export, &(app->sectors[sectorid]));
	import_ceil_slope(export, &(app->sectors[sectorid]));
		ft_printf("sectorid = %i corners count: %i, floor slope %f, ceil slope %f\n", sectorid, app->sectors[sectorid].corner_count, app->sectors[sectorid].floor_slope_angles.x, app->sectors[sectorid].ceiling_slope_angles.x);
}

//open a file
int	import_file(t_app *app, char *path)
{
	int	fd;
	t_exportsector *export;
	size_t counter = 0;
	size_t sector_count = 0;
	t_sector	*sectors;


	fd = open(path, O_RDONLY, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	if (read(fd, &sector_count,(sizeof(size_t))) == -1)
		exit_error(MSG_ERROR_FILE_READ);
	
	sectors = (t_sector *)malloc(sizeof(t_sector) * sector_count); 
	app->sectors = sectors;
	while(counter < sector_count)
	{
		if (read(fd, export,sizeof(t_exportsector)) == -1)
			exit_error(MSG_ERROR_FILE_READ);
		read_sector(app, export, counter, sector_count);
		counter++;
	}
	free(export);
	ft_printf("sector_count=%i\n",sector_count);
	close(fd);
	return (0);
}