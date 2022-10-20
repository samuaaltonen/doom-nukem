/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/20 14:21:47 by htahvana         ###   ########.fr       */
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