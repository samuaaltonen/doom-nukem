/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/22 17:11:03 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	list_to_export(t_exportsector *export, t_vec2_lst *list, int count)
{
	int			i;
	t_vec2_lst	*tmp;

	i = 0;
	tmp = list;
	while (i < count)
	{
		export->corners[i].x = tmp->point.x;
		export->corners[i].y = tmp->point.y;
		export->wall_textures[i] = tmp->tex;
		export->wall_types[i] = tmp->type;
		tmp = tmp->next;
		i++;
	}
}

static void	member_export(t_app *app, t_exportsector *export,
											t_sector_lst *sector)
{
	int		i;

	i = 0;
	while (sector->member_sectors[i])
	{
		export->member_sectors[i] = get_sector_id(app,
				sector->member_sectors[i]);
		ft_printf("%i\n", export->member_sectors[i]);
		i++;
	}
	while (i < MAX_MEMBER_SECTORS)
	{
		export->member_sectors[i] = -1;
		i++;
	}
}

int	get_line_id(t_vec2_lst *list, t_vec2_lst *wall)
{
	int		i;

	if (!wall)
		return (-1);
	i = 0;
	while (wall != list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

/**
 * @brief Writes sector data to an exportable format
 * 
 * @param app 
 * @param sector 
 * @param export 
 */
void	write_sector(t_app *app, t_sector_lst *sector, t_exportsector *export)
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
	export->floor_slope_opposite = get_line_id(sector->wall_list, sector->floor_slope_opposite);
	export->floor_slope_position = get_line_id(sector->wall_list, sector->floor_slope_wall);
	export->ceil_slope_height = sector->ceil_slope_height;
	export->ceil_slope_opposite = get_line_id(sector->wall_list, sector->ceil_slope_opposite);
	export->ceil_slope_position = get_line_id(sector->wall_list, sector->ceil_slope_wall);
}
static int as_bits(t_app *app, t_weapon weapons[MAX_WEAPONS])
{
	int	inventory;
	int	i;

	inventory = 0;
	i = 0;
	while (i < MAX_WEAPONS)
	{
		(void)weapons;
		//if(weapons[i].enabled)
		if(i == app->player.selected_weapon)
			inventory |= 1 << i;
		i++;
	}
	return (inventory);
}

static void write_player(t_app *app, t_export_player *export)
{
	export->position = app->player.position;
	export->direction = app->player.direction;
	export->sector = get_sector_id(app,app->player.sector);
	export->health = app->player.health;
	export->weapons = as_bits(app, app->player.weapons);
	export->armor = app->player.armor[app->player.selected_armor].defence;
	export->inventory = app->player.inventory;
}

static void write_objects(t_app *app, t_export_object *objects)
{
	t_export_object temp;
	int	i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		temp.pos = app->objects[i].position;
		temp.sector = get_sector_id(app, app->objects[i].sector);
		temp.type = app->objects[i].type;
		if(temp.type != 0)
				ft_printf("object exported %i\n", i);
		temp.var = app->objects[i].var;
		(objects[i]) = temp;
		i++;
	}
}

static void write_interactions(t_app *app, t_export_interaction *interactions)
{
	t_export_interaction temp;
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{

		temp.activation_object = get_object_id(app,app->interactions[i].activation_object);
		temp.activation_sector = get_sector_id(app,app->interactions[i].activation_sector);
		if(temp.activation_sector)
			temp.activation_wall = get_line_id(app->interactions[i].activation_sector->wall_list, app->interactions[i].activation_wall);
		temp.event_id = app->interactions[i].event_id;
		temp.target_sector = get_sector_id(app, app->interactions[i].target_sector);
		temp.variable = app->interactions[i].variable;
		(interactions[i]) = temp;
		i++;
	}
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
	int						fd;
	t_sector_lst			*tmp;
	t_exportsector			*export;
	size_t					counter;
	size_t					sector_count;
	t_export_player			player;
	t_export_object			objects[MAX_OBJECTS];
	t_export_interaction	interactions[MAX_INTERACTIONS];

	counter = 0;
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	fd = open(path, O_WRONLY | O_CREAT, 0755);
	if (fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	write_player(app, &player);
 	if (write(fd, &player, sizeof(t_export_player)) == -1)
		exit_error("Player Write Error\n");
	sector_count = ft_lstlen(app->sectors);
	if (write(fd, &sector_count, sizeof(sector_count)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	tmp = app->sectors;
	while (counter++ < sector_count)
	{
		write_sector(app, tmp, export);
		ft_printf("exported sector corners %i\n", export->corner_count);
		if (write(fd, export, sizeof(t_exportsector)) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		tmp = tmp->next;
	}
	write_objects(app, (t_export_object *)&objects);
 	if (write(fd, objects, sizeof(t_export_object) * MAX_OBJECTS) == -1)
		exit_error("object write error\n");
	write_interactions(app, (t_export_interaction *)&interactions);
	for(int i = 0; i < MAX_INTERACTIONS;i++)
		ft_printf("read interactions id %i, target sector%p, wall%p, object%p\n",app->interactions[i].event_id, app->interactions[i].activation_wall, app->interactions[i].activation_object);

	if (write(fd, interactions, sizeof(t_export_interaction) * MAX_INTERACTIONS) == -1)
		exit_error("interaction write error\n");
	free(export);
	close(fd);
	return (0);
}
