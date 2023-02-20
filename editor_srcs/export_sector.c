/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:11:57 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 13:12:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Copies data from list format to export format.
 * 
 * @param export 
 * @param list 
 * @param count 
 */
static void	list_to_export(t_export_sector *export, t_wall_list *list,
	int count)
{
	int			i;
	t_wall_list	*tmp;

	i = 0;
	tmp = list;
	while (i < count)
	{
		export->corners[i].x = tmp->point.x;
		export->corners[i].y = tmp->point.y;
		export->wall_textures[i] = tmp->tex;
		export->wall_types[i] = tmp->type;
		export->wall_decor[i] = tmp->decor;
		export->decor_offset[i] = tmp->decor_offset;
		tmp = tmp->next;
		i++;
	}
}

/**
 * @brief Exports member sectors.
 * 
 * @param app 
 * @param export 
 * @param sector 
 */
static void	member_export(t_app *app, t_export_sector *export,
		t_sector_list *sector)
{
	int		i;

	i = 0;
	while (i < MAX_MEMBER_SECTORS && sector->member_sectors[i])
	{
		export->member_sectors[i] = get_sector_id(app,
				sector->member_sectors[i]);
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
void	write_sector(t_app *app, t_sector_list *sector, t_export_sector *export)
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
	export->floor_slope_opposite = get_wall_id(sector->wall_list,
			sector->floor_slope_opposite);
	export->floor_slope_position = get_wall_id(sector->wall_list,
			sector->floor_slope_wall);
	export->ceil_slope_height = sector->ceil_slope_height;
	export->ceil_slope_opposite = get_wall_id(sector->wall_list,
			sector->ceil_slope_opposite);
	export->ceil_slope_position = get_wall_id(sector->wall_list,
			sector->ceil_slope_wall);
}

/**
 * @brief Exports sectors.
 * 
 * @param app 
 * @param header 
 * @param fd 
 */
void	export_sectors(t_app *app, t_level_header header, int fd,
	t_import_info *info)
{
	int				i;
	t_sector_list	*tmp;
	t_export_sector	export;

	ft_bzero(&export, sizeof(t_export_sector));
	tmp = app->sectors;
	i = 0;
	while (i < header.sector_count)
	{
		write_sector(app, tmp, &export);
		if (write(fd, &export, sizeof(t_export_sector)) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		tmp = tmp->next;
		i++;
	}
	info->length = 1000;
	info->imported = 1;
	export_update_progress(info);
}
