/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/19 13:21:58 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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

//read sector data from export
void read_sector(t_sectorlist *sector, t_exportsector *export)
{
	sector->ceiling_height = export->ceiling_height;
	sector->ceiling_slope_height = export->ceiling_slope_height;
	sector->corner_count = export->corner_count;
	sector->wall_list = NULL;
	export_to_list(export, &sector->wall_list, export->corner_count);
	ft_memcpy(sector->member_links,export->member_sectors, MAX_MEMBER_SECTORS * sizeof(int));
	ft_printf("0th %i, 1st %i, 2nd %i, 3rd %i\n",sector->member_links[0], sector->member_links[1],sector->member_links[2], sector->member_links[3]);
	sector->ceiling_slope_opposite = ft_lstindex(sector->wall_list, export->ceiling_slope_opposite);
	sector->ceiling_slope_wall = ft_lstindex(sector->wall_list, export->ceiling_slope_position);
	sector->ceiling_texture = export->ceiling_texture;
	sector->floor_height = export->floor_height;
	sector->floor_slope_height = export->floor_slope_height;
	sector->floor_slope_opposite = ft_lstindex(sector->wall_list, export->floor_slope_opposite);
	sector->floor_slope_wall = ft_lstindex(sector->wall_list, export->floor_slope_position);
	sector->floor_texture = export->floor_texture;
	sector->parent_sector = NULL;
	sector->next = NULL;
}

/**
 * reads a exportsector and makes a sector.
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

//open a file
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
