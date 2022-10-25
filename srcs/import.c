/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/25 14:28:51 by saaltone         ###   ########.fr       */
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

static void	import_slopes(t_app *app, t_exportsector *export, t_sector *sector)
{
	t_vector2 point;
	t_vector2 linedst;
	t_vector2 opposite;
	t_vector2 perp;
	(void)app;

	if(export->floor_slope_position == -1)
	{
		return ;
	}
	point.x = sector->corners[export->floor_slope_position].x;
	point.y = sector->corners[export->floor_slope_position].y;
	if(export->floor_slope_position < sector->corner_count)
	{
		linedst.x = sector->corners[export->floor_slope_position + 1].x;
		linedst.y = sector->corners[export->floor_slope_position + 1].y;
	}
	else
	{
		linedst.x = sector->corners[0].x;
		linedst.y = sector->corners[0].y;
	}
	opposite.x = sector->corners[export->floor_slope_opposite].x;
	opposite.y = sector->corners[export->floor_slope_opposite].y;

	perp = ft_vector_perpendicular((t_vector2){linedst.x - point.x, linedst.y - point.y});
	
	ft_line_intersection(ft_line_resize( \
		(t_line){point, linedst}, MAX_LINE_LENGTH, 2), \
		ft_line_resize((t_line){(t_vector2){opposite.x, opposite.y}, \
		(t_vector2){perp.x + opposite.x, perp.y + opposite.y}}, \
		MAX_LINE_LENGTH, 2),&point);
	
	double height =  export->floor_slope_height - export->floor_height;

	sector->floor_slope_angles.x = atan(height / ft_vector_length((t_vector2){opposite.x - point.x, opposite.y - point.y}));
	sector->floor_slope_angles.y = ft_vector_angle(linedst,(t_vector2){0.f,1.f});
	ft_printf("INTERSECTION POINT: x%f y%f\n", RADIAN_IN_DEG * sector->floor_slope_angles.x, RADIAN_IN_DEG * sector->floor_slope_angles.y);
	
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
	import_slopes(app, export, &(app->sectors[sectorid]));
		ft_printf("sectorid = %i corners count: %i\n", sectorid, app->sectors[sectorid].corner_count);
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
	ft_printf("sector_count=%i\n",sector_count);
	close(fd);
	return (0);
}