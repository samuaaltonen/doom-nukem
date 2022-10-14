/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/14 15:06:35 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	list_to_export(t_exportsector *export, t_vec2list *list, int count)
{
	int i;
	t_vec2list *tmp;

	i = 0;
	tmp = list;
	while(i < count)
	{
		export->corners[i].x = tmp->point.x;
		export->corners[i].y = tmp->point.y;
		export->wall_textures[i] = tmp->wall_texture;
		export->wall_types[i] = tmp->wall_type;
		tmp = tmp->next;
		i++;
	}
}

//construct string
void write_sector(t_sectorlist *sector, t_exportsector *export)
{
	//export->ceiling_height = sector->ceiling_height;
	export->ceiling_height = 1;
	export->ceiling_slope_height = 0;
	export->ceiling_slope_opposite = 0;
	export->ceiling_slope_position = 0;
	export->ceiling_texture = 0;
	export->corner_count = sector->corner_count;
	list_to_export(export, sector->wall_list, export->corner_count);
	export->floor_height = sector->floor_height;
	export->floor_slope_height = 0;
	export->floor_slope_opposite = 0;
	export->floor_slope_position = 0;
	export->floor_texture = 0;
} 

size_t	ft_lstlen(t_sectorlist *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}


//open a file
int	file_open(t_app *app, char *path)
{
	(void)app;
	int fd;
	t_exportsector *export;
	size_t	sectorcountTEMP = 0;
	size_t	sectors;
	t_sectorlist *tmp;

	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	fd = open(path, O_WRONLY | O_CREAT, 0755);
	if(fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
		
	sectors = ft_lstlen(app->sectors);
	write(fd,&sectors,sizeof(sectors));
	tmp = app->sectors;
	while(sectorcountTEMP++ < sectors)
	{
		write_sector(tmp, export);
		write(fd, export, sizeof(t_exportsector));
		tmp = tmp->next;
	}
	free(export);
	close(fd);
	return (0);
}

//write list points to file

//close file