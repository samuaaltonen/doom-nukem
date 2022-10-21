/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:27:27 by htahvana         ###   ########.fr       */
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
static void	export_to_list(t_exportsector *export, t_vec2list **list, int count)
{
	int			i;
	t_vec2list	*tmp;
	t_vector2	point;

	if(!export)
		return ;
	point.x = export->corners[0].x;
	point.y = export->corners[0].y;
	tmp = new_vector_list(&point);
	*list = tmp;
	tmp->wall_texture = export->wall_textures[0];
	tmp->wall_type = export->wall_types[0];
	i = 1;
	while(i < count)
	{
		point.x = export->corners[i].x;
		point.y = export->corners[i].y;
		tmp->next = new_vector_list(&point);
		put_to_vector_list(list, tmp->next);
		tmp->next->wall_texture = export->wall_textures[i];
		tmp->next->wall_type = export->wall_types[i];
		tmp = tmp->next;
		i++;
	}
	tmp->next = *list;
}

//returns element out the link at the index
t_vec2list	*ft_lstindex(t_vec2list *lst, size_t index)
{
	size_t	i;
	t_vec2list	*temp;

	i = 0;
	temp = lst;
	if (index == 0)
		return (lst);
	if (temp == NULL)
		return (NULL);
	while (i < index)
	{
		if (temp->next)
			temp = temp->next;
		else
			return (NULL);
		i++;
	}
	return (temp);
}

/**
 * @brief reads values from exported sector and writes them into sector
 * 
 * @param sector 
 * @param export 
 */
void read_sector(t_sectorlist *sector, t_exportsector *export)
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
	sector->floor_slope_opposite = ft_lstindex(sector->wall_list, export->floor_slope_opposite);
	sector->floor_slope_wall = ft_lstindex(sector->wall_list, export->floor_slope_position);
	sector->ceil_slope_height = export->ceil_slope_height;
	sector->ceil_slope_opposite = ft_lstindex(sector->wall_list, export->ceil_slope_opposite);
	sector->ceil_slope_wall = ft_lstindex(sector->wall_list, export->ceil_slope_position);
	sector->parent_sector = NULL;
	sector->next = NULL;
	ft_printf("0th %i, 1st %i, 2nd %i, 3rd %i\n",sector->member_links[0], sector->member_links[1],sector->member_links[2], sector->member_links[3]);
}

/**
 * @brief reads exported sector data, allocates and returns a new sector
 * 
 * @param export 
 * @return t_sectorlist* 
 */
t_sectorlist	*read_sector_list(t_exportsector *export)
{
	t_sectorlist	*new;
	new = (t_sectorlist *)malloc(sizeof(t_sectorlist));
	if (!new)
		return (NULL);
	read_sector(new, export);
	return (new);
}

static t_sectorlist *sector_by_index(t_app *app, int index)
{
	t_sectorlist *head;
	int i;

	i = 0;
	head = app->sectors;
	while (head && i != index)
	{
		head = head->next;
		i++;
	}
	return (head);
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
	t_sectorlist *head;

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
	t_sectorlist *new;
	size_t counter = 0;
	size_t sector_count;

	fd = open(path, O_RDONLY, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	read(fd, &sector_count,(sizeof(size_t)));
	while(counter++ < sector_count)
	{
		read(fd, export,sizeof(t_exportsector));
		new = read_sector_list(export);
		put_sector_lst(app, new);
	}
	close(fd);
	relink_sectors(app);
	return (0);
}
