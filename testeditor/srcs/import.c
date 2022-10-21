/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 17:25:17 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief creates a pointer list from saved point data
 * 
 * @param export 
 * @param list 
 * @param count 
 */
static void	export_to_list(t_exportsector *export, t_vec2_lst **list, int count)
{
	int			i;
	t_vec2_lst	*tmp;
	t_vector2	point;

	if(!export)
		return ;
	point.x = export->corners[0].x;
	point.y = export->corners[0].y;
	tmp = new_vector_list(&point);
	*list = tmp;
	tmp->tex = export->wall_textures[0];
	tmp->type = export->wall_types[0];
	i = 1;
	while(i < count)
	{
		point.x = export->corners[i].x;
		point.y = export->corners[i].y;
		tmp->next = new_vector_list(&point);
		put_to_vector_list(list, tmp->next);
		tmp->next->tex = export->wall_textures[i];
		tmp->next->type = export->wall_types[i];
		tmp = tmp->next;
		i++;
	}
	tmp->next = *list;
}

/**
 * @brief reads values from exported sector and writes them into sector
 * 
 * @param sector 
 * @param export 
 */
void read_sector(t_sector_lst *sector, t_exportsector *export)
{
	sector->corner_count = export->corner_count;
	sector->wall_list = NULL;
	export_to_list(export, &sector->wall_list, export->corner_count);
	ft_memcpy(sector->member_links,export->member_sectors, MAX_MEMBER_SECTORS * sizeof(int));
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
	if(export->floor_slope_opposite != -1)
		sector->floor_slope_opposite = ft_lstindex(sector->wall_list, export->floor_slope_opposite);
	if(export->floor_slope_position != -1)
		sector->floor_slope_wall = ft_lstindex(sector->wall_list, export->floor_slope_position);
	sector->ceil_slope_height = export->ceil_slope_height;
	if(export->ceil_slope_opposite != -1)
		sector->ceil_slope_opposite = ft_lstindex(sector->wall_list, export->ceil_slope_opposite);
	if(export->floor_slope_position != -1)
		sector->ceil_slope_wall = ft_lstindex(sector->wall_list, export->ceil_slope_position);
	sector->parent_sector = NULL;
	sector->next = NULL;
	ft_printf("0th %i, 1st %i, 2nd %i, 3rd %i\n",sector->member_links[0], sector->member_links[1],sector->member_links[2], sector->member_links[3]);
}

/**
 * @brief reads exported sector data, allocates and returns a new sector
 * 
 * @param export 
 * @return t_sector_lst* 
 */
t_sector_lst	*read_sector_list(t_exportsector *export)
{
	t_sector_lst	*new;
	new = (t_sector_lst *)malloc(sizeof(t_sector_lst));
	if (!new)
		return (NULL);
	read_sector(new, export);
	return (new);
}

/**
 * @brief relinks the pointer references of sectors
 * 	using integer values in saved file
 * 
 * @param app 
 */
void	relink_sectors(t_app *app)
{
	int		i;
	t_sector_lst *head;

	head = app->sectors;
	while (head)
	{
		i = 0;
		while (i < MAX_MEMBER_SECTORS)
		{
			if(head->member_links[i] != -1)
			{
				head->member_sectors[i] = sector_by_index(app, head->member_links[i]);
				head->member_sectors[i]->parent_sector = head;
			}
			else
				head->member_sectors[i] = NULL;
			
			i++;
		}
		head = head->next;
	}

}

/**
 * @brief Opens a file from the given path
 * 	reads all sector data into the sector list
 * 
 * @param app 
 * @param path 
 * @return int 
 */
int	import_file(t_app *app, char *path)
{
	int	fd;
	t_exportsector *export;
	t_sector_lst *new;
	size_t counter = 0;
	size_t sector_count;

	fd = open(path, O_RDONLY, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	if (read(fd, &sector_count,(sizeof(size_t))) == -1)
		exit_error(MSG_ERROR_FILE_READ);
	while(counter++ < sector_count)
	{
		if (read(fd, export,sizeof(t_exportsector)) == -1)
			exit_error(MSG_ERROR_FILE_READ);
		new = read_sector_list(export);
		put_sector_lst(app, new);
	}
	close(fd);
	relink_sectors(app);
	return (0);
}
