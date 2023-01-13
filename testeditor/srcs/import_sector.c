/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:36:17 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/13 15:26:29 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Creates a pointer list from saved point data.
 * 
 * @param export 
 * @param list 
 * @param count 
 */
static void	export_to_list(t_export_sector *export, t_vec2_lst **list,
	int count)
{
	int			i;
	t_vec2_lst	*tmp;
	t_vector2	point;

	point = export->corners[0];
	tmp = new_vector_list(&point);
	*list = tmp;
	tmp->tex = export->wall_textures[0];
	tmp->type = export->wall_types[0];
	tmp->decor = export->wall_decor[0];
	tmp->decor_offset = export->decor_offset[0];
	i = 0;
	while (++i < count)
	{
		point = export->corners[i];
		tmp->next = new_vector_list(&point);
		put_to_vector_list(list, tmp->next);
		tmp->next->tex = export->wall_textures[i];
		tmp->next->type = export->wall_types[i];
		tmp->next->decor = export->wall_decor[i];
		tmp->next->decor_offset = export->decor_offset[i];
		tmp = tmp->next;
	}
	tmp->next = *list;
}

/**
 * @brief Reads values from exported sector and writes them into sector.
 * 
 * @param sector 
 * @param export 
 */
void	read_sector(t_sector_lst *sector, t_export_sector *export)
{
	sector->light = export->light;
	sector->floor_height = export->floor_height;
	sector->ceil_height = export->ceil_height;
	sector->floor_tex = export->floor_tex;
	sector->floor_tex_offset = export->floor_tex_offset;
	sector->ceil_tex = export->ceil_tex;
	sector->ceil_tex_offset = export->ceil_tex_offset;
	sector->floor_slope_height = export->floor_slope_height;
	sector->floor_slope_opposite = 0;
	sector->floor_slope_wall = 0;
	sector->ceil_slope_opposite = 0;
	sector->ceil_slope_wall = 0;
	if (export->floor_slope_opposite != -1)
		sector->floor_slope_opposite = ft_lstindex(sector->wall_list,
				export->floor_slope_opposite);
	if (export->floor_slope_position != -1)
		sector->floor_slope_wall = ft_lstindex(sector->wall_list,
				export->floor_slope_position);
	sector->ceil_slope_height = export->ceil_slope_height;
	if (export->ceil_slope_opposite != -1)
		sector->ceil_slope_opposite = ft_lstindex(sector->wall_list,
				export->ceil_slope_opposite);
	if (export->ceil_slope_position != -1)
		sector->ceil_slope_wall = ft_lstindex(sector->wall_list,
				export->ceil_slope_position);
}

/**
 * @brief Reads exported sector data, allocates and returns a new sector.
 * 
 * @param export 
 * @return t_sector_lst* 
 */
t_sector_lst	*read_sector_list(t_export_sector *export)
{
	t_sector_lst	*new;

	new = (t_sector_lst *)malloc(sizeof(t_sector_lst));
	if (!new)
		exit_error(MSG_ERROR_ALLOC);
	new->corner_count = export->corner_count;
	new->wall_list = NULL;
	export_to_list(export, &new->wall_list, export->corner_count);
	ft_memcpy(new->member_links, export->member_sectors,
		MAX_MEMBER_SECTORS * sizeof(int));
	new->parent_sector = NULL;
	new->next = NULL;
	read_sector(new, export);
	return (new);
}

/**
 * @brief Imports sectors.
 * 
 * @param app 
 * @param info 
 */
void	import_sectors(t_app *app, t_import_info *info)
{
	t_export_sector	export;
	int				i;

	if (info->header.sector_count > MAX_SECTOR_COUNT
		|| sizeof(t_export_sector) * (size_t)info->header.sector_count
		> (size_t)(info->length - info->imported))
		exit_error(MSG_ERROR_IMPORT_SECTOR);
	app->sector_count = info->header.sector_count;
	i = 0;
	while (i < info->header.sector_count)
	{
		ft_memcpy(&export, info->data + info->imported,
			sizeof(t_export_sector));
		level_validation_sector(app, &export);
		info->imported += (int) sizeof(t_export_sector);
		put_sector_lst(app, read_sector_list(&export));
		i++;
	}
}
