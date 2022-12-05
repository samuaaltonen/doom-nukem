/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/01 15:24:43 by saaltone         ###   ########.fr       */
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

	if (!export)
		return ;
	point.x = export->corners[0].x;
	point.y = export->corners[0].y;
	tmp = new_vector_list(&point);
	*list = tmp;
	tmp->tex = export->wall_textures[0];
	tmp->type = export->wall_types[0];
	tmp->decor = export->wall_decor[0];
	tmp->decor_offset = export->decor_offset[0];
	i = 1;
	while (i < count)
	{
		point.x = export->corners[i].x;
		point.y = export->corners[i].y;
		tmp->next = new_vector_list(&point);
		put_to_vector_list(list, tmp->next);
		tmp->next->tex = export->wall_textures[i];
		tmp->next->type = export->wall_types[i];
		tmp->next->decor = export->wall_decor[i];
		tmp->next->decor_offset = export->decor_offset[i];
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
void	read_sector(t_sector_lst *sector, t_exportsector *export)
{
	sector->corner_count = export->corner_count;
	sector->wall_list = NULL;
	export_to_list(export, &sector->wall_list, export->corner_count);
	ft_memcpy(sector->member_links, export->member_sectors, MAX_MEMBER_SECTORS * sizeof(int));
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
		sector->floor_slope_opposite = ft_lstindex(sector->wall_list, export->floor_slope_opposite);
	if (export->floor_slope_position != -1)
		sector->floor_slope_wall = ft_lstindex(sector->wall_list, export->floor_slope_position);
	sector->ceil_slope_height = export->ceil_slope_height;
	if (export->ceil_slope_opposite != -1)
		sector->ceil_slope_opposite = ft_lstindex(sector->wall_list, export->ceil_slope_opposite);
	if (export->ceil_slope_position != -1)
		sector->ceil_slope_wall = ft_lstindex(sector->wall_list, export->ceil_slope_position);
	sector->parent_sector = NULL;
	sector->next = NULL;
	ft_printf("0th %i, 1st %i, 2nd %i, 3rd %i\n", sector->member_links[0], sector->member_links[1], sector->member_links[2], sector->member_links[3]);
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
	int				i;
	t_sector_lst	*head;

	head = app->sectors;
	while (head)
	{
		i = 0;
		while (i < MAX_MEMBER_SECTORS)
		{
			if (head->member_links[i] != -1)
			{
				head->member_sectors[i] = sector_by_index(app,
						head->member_links[i]);
				head->member_sectors[i]->parent_sector = head;
			}
			else
				head->member_sectors[i] = NULL;
			i++;
		}
		head = head->next;
	}
}

static void from_bits(t_app *app, int export, t_weapon *weapons)
{
	int	i;

	i = 0;
	while (i < MAX_WEAPONS)
	{
		if (export & 1)
		{	
			weapons[i].enabled = TRUE;
			app->player.selected_weapon = i;
		}
		export >>= 1;
		i++;
	}
}

static void read_player(t_app *app, t_export_player *player)
{
	app->player_edit = FALSE;
	app->player_menu = FALSE;
	app->player.position = player->position;
	app->player.direction = player->direction;
	app->player.sector = sector_by_index(app, player->sector);
	app->player.health = player->health;
	from_bits(app, player->weapons, app->player.weapons);
	// int	i;
	// i = 0;
	// while (i < MAX_ARMOR)
	// {
	// 	if (app->player.armor[i].defence == player->armor)
	// 		app->player.selected_armor = i;
	// 	i++;
	// }
	app->player.inventory = player->inventory;
}

static void	read_objects(t_app *app, t_export_object *export)
{
	t_object	temp;
	int			i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		temp.position = export[i].pos;
		temp.sector =  sector_by_index(app, export[i].sector);
		temp.type = export[i].type;
		temp.var = export[i].var;
		(app->objects[i]) = temp;
		i++;
	}
}

static t_vec2_lst *line_by_index(t_sector_lst *sector, int index)
{
	int	i;
	t_vec2_lst *head;

	i = 0;
	if (!sector || index == -1)
		return (NULL);
	head = sector->wall_list;
	while (i < MAX_SECTOR_CORNERS)
	{
		if(i == index)
			return (head);
		head = head->next;
		i++;
	}
	return (NULL);
}

static void	read_interactions(t_app *app, t_export_interaction *export)
{
	t_interaction	temp;
	int				i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		temp.event_id = export[i].event_id;
		temp.variable = export[i].variable;
		temp.activation_sector = sector_by_index(app, export[i].activation_sector);
		temp.activation_wall = line_by_index(temp.activation_sector, export[i].activation_wall);
		if(export[i].activation_object == -1)
			temp.activation_object = NULL;
		else
			temp.activation_object = &(app->objects[export[i].activation_object]);
		temp.target_sector = sector_by_index(app, export[i].target_sector);
		app->interactions[i] = temp;
		i++;
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
	int				fd;
	t_exportsector	*export;
	t_sector_lst	*new;
	int				counter;
	t_export_player	player;
	t_export_object	objects[MAX_OBJECTS];
	t_export_interaction	interactions[MAX_INTERACTIONS];
	t_level_header			header;


	counter = 0;
	fd = open(path, O_RDONLY, 0755);
	if (fd < 0)
		exit_error("FILE OPEN ERROR TEMP!");
	if (read(fd, &header, (sizeof(t_level_header))) == -1)
		exit_error(MSG_ERROR_FILE_READ);
	app->interaction_count = header.interaction_count;
	app->object_count = header.object_count;
	if (read(fd, &player, sizeof(t_export_player)) == -1)
			exit_error("player read error\n");
	read_player(app, &player);
	export = (t_exportsector *)ft_memalloc(sizeof(t_exportsector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	while (counter++ < header.sector_count)
	{
		if (read(fd, export, sizeof(t_exportsector)) == -1)
			exit_error(MSG_ERROR_FILE_READ);
		new = read_sector_list(export);
		put_sector_lst(app, new);
	}
	if (read(fd,&objects, sizeof(t_export_object) * MAX_OBJECTS) ==  -1)
		exit_error("Object read error\n");
	read_objects(app, (t_export_object *)&objects);
	for(int i = 0; i < MAX_OBJECTS;i++)
		ft_printf("object id %i, type %i\n", i, app->objects[i].type);
	if (read(fd, &interactions, sizeof(t_export_interaction) * MAX_INTERACTIONS) == -1)
		exit_error("Interaction read error\n");
	read_interactions(app, (t_export_interaction *)&interactions);
	for(int i = 0; i < MAX_INTERACTIONS;i++)
		ft_printf("read interactions id %i, activation sector%i, wall%i, object%i\n",interactions[i].event_id, interactions[i].activation_sector, interactions[i].activation_wall, interactions[i].activation_object);
	for(int i = 0; i < MAX_INTERACTIONS;i++)
		ft_printf("pointer interactions id %i, activation sector%p, wall%p, object%p\n",app->interactions[i].event_id, app->interactions[i].activation_sector, app->interactions[i].activation_wall, app->interactions[i].activation_object);

	close(fd);
	app->player.sector = sector_by_index(app,player.sector);
	relink_sectors(app);
	return (0);
}
