/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/14 14:43:12 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	export_to_array(t_app *app, t_exportsector *export, int sectorid)
{
	ft_memcpy(app->sectors[sectorid].corners, export->corners, export->corner_count * sizeof(t_vector2));
	ft_memcpy(app->sectors[sectorid].wall_textures, export->wall_textures, export->corner_count * sizeof(int));
	ft_memcpy(app->sectors[sectorid].wall_types, export->wall_types, export->corner_count *  sizeof(int));
}

//read sector data from export
static void read_sector(t_app *app, t_exportsector *export, int sectorid, int sector_count)
{
	app->sectors[sectorid].corner_count = export->corner_count;
	export_to_array(app, export, sectorid);
	app->sectors[sectorid].ceiling_texture = export->ceiling_texture;
	app->sectors[sectorid].floor_texture = export->floor_texture;
	app->sectors[sectorid].ceiling_height = export->ceiling_height;
	app->sectors[sectorid].floor_height = export->floor_height;
	app->sectors[sectorid].parent_sector = 0;
		ft_printf("sectorid = %i ", sectorid);

	//temporary
	if(sectorid == 0)
	{
		app->sectors[sectorid].member_sectors[sector_count] = -1;
		while(--sector_count > 0)
		{
			app->sectors[sectorid].member_sectors[sector_count] = sector_count;
		}
			app->sectors[sectorid].member_sectors[sector_count] = -1;

	}
	else
		app->sectors[sectorid].member_sectors[0] = -1;
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

	read(fd, &sector_count,(sizeof(size_t)));
	
	sectors = (t_sector *)malloc(sizeof(t_sector) * sector_count); 
	app->sectors = sectors;
	while(counter < sector_count)
	{
		read(fd, export,sizeof(t_exportsector));
		ft_printf("export data corners=%i\n", export->corner_count);
		read_sector(app, export, counter, sector_count);
		counter++;
	}
	ft_printf("sector_count=%i\n",sector_count);
	ft_printf("sector data, corner count=%i, x%f, y%f, membersect:%i,%i\n", app->sectors[0].corner_count, app->sectors[0].corners[0].x, app->sectors[0].corners[0].y, app->sectors[0].member_sectors[0], app->sectors[0].member_sectors[1]);
	ft_printf("sector data, corner count=%i, x%f, y%f, membersect:%i,%i\n", app->sectors[1].corner_count, app->sectors[1].corners[1].x, app->sectors[1].corners[1].y, app->sectors[1].member_sectors[0], app->sectors[1].member_sectors[1]);

	close(fd);
	return (0);
}