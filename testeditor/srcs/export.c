/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 14:33:54 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	list_to_export(t_exportsector *export, t_vec2_lst *list, int count)
{
	int i;
	t_vec2_lst *tmp;

	i = 0;
	tmp = list;
	while(i < count)
	{
		export->corners[i].x = tmp->point.x;
		export->corners[i].y = tmp->point.y;
		export->wall_textures[i] = tmp->tex;
		export->wall_types[i] = tmp->type;
		tmp = tmp->next;
		i++;
	}
}

static void	member_export(t_app *app, t_exportsector *export, t_sector_lst *sector)
{
	int	i;

	i = 0;
	while (sector->member_sectors[i])
	{
		export->member_sectors[i] = get_sector_id(app, sector->member_sectors[i]);
		ft_printf("%i\n", export->member_sectors[i]);
		i++;
	}
	while (i < MAX_MEMBER_SECTORS)
	{
		export->member_sectors[i] = -1;
		i++;
	}
}

/**
 * @brief Writes sector data to an exportable format
 * 
 * @param app 
 * @param sector 
 * @param export 
 */
void write_sector(t_app *app, t_sector_lst *sector, t_exportsector *export)
{
	export->corner_count = sector->corner_count;
	list_to_export(export, sector->wall_list, export->corner_count);
	member_export(app, export, sector);
	export->parent_sector = get_sector_id(app, sector->parent_sector);
	export->light = sector->light;
	export->floor_height = sector->floor_height;
	export->ceil_height = sector->ceil_height;
	export->floor_tex = sector->floor_tex;
	export->floor_tex_offset = -1;
	export->ceil_tex = sector->ceil_tex;
	export->ceil_tex_offset = -1;
	export->floor_slope_height = sector->floor_slope_height;
	export->floor_slope_opposite = 0;
	export->floor_slope_position = 0;
	export->ceil_slope_height = sector->ceil_slope_height;
	export->ceil_slope_opposite = 0;
	export->ceil_slope_position = 0;
} 

/**
 * @brief Opens or creates a file at path, writes map data to it
 * 
 * @param app 
 * @param path 
 * @return int 
 */
int	export_file(t_app *app, char *path)
{
	int fd;
	t_exportsector *export;
	size_t	counter = 0;
	size_t	sector_count;
	t_sector_lst *tmp;

	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	fd = open(path, O_WRONLY | O_CREAT, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	sector_count = ft_lstlen(app->sectors);
	write(fd,&sector_count,sizeof(sector_count));
	tmp = app->sectors;
	while(counter++ < sector_count)
	{
		write_sector(app, tmp, export);
		ft_printf("exported sector corners %i\n", export->corner_count);
		write(fd, export, sizeof(t_exportsector));
		tmp = tmp->next;
	}
	free(export);
	close(fd);
	return (0);
}
