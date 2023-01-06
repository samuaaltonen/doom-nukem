/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/06 15:17:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	list_to_export(t_export_sector *export, t_vec2_lst *list, int count)
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
		export->wall_decor[i] = tmp->decor;
		export->decor_offset[i] = tmp->decor_offset;
		tmp = tmp->next;
		i++;
	}
}

static void	member_export(t_app *app, t_export_sector *export,
											t_sector_lst *sector)
{
	int		i;

	i = 0;
	while (sector->member_sectors[i])
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
void	write_sector(t_app *app, t_sector_lst *sector, t_export_sector *export)
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
	export->armor = app->player.armor;
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
		if (app->objects[i].sector)
			temp.elevation = app->objects[i].sector->floor_height;
		else
			temp.elevation = 0.f;
		temp.sector = get_sector_id(app, app->objects[i].sector);
		temp.type = app->objects[i].type;
		temp.var = app->objects[i].var;
		objects[i] = temp;
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
		if(temp.activation_sector != -1 && app->interactions[i].activation_wall)
			temp.activation_wall = get_line_id(app->interactions[i].activation_sector->wall_list, app->interactions[i].activation_wall);
		else
			temp.activation_wall = -1;
		temp.event_id = app->interactions[i].event_id;
		temp.target_sector = get_sector_id(app, app->interactions[i].target_sector);
		temp.variable = app->interactions[i].variable;
		temp.editable = app->interactions[i].editable;
		interactions[i] = temp;
		i++;
	}
}

void	export_surface(t_level_header *header, int index, int fd,
	const char *path)
{
	SDL_Surface	*surface;

	surface = bmp_to_surface(path);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_LOAD);
	header->asset_info[index].width = surface->w;
	header->asset_info[index].height = surface->h;
	header->asset_info[index].size = surface->w * surface->h
		* IMAGE_PIXEL_BYTES;
	if (write(fd, surface->pixels, header->asset_info[index].size) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
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
	int						counter;
	t_sector_lst			*tmp;
	t_export_sector			*export;
	t_export_player			player;
	t_export_object			objects[MAX_OBJECTS];
	t_export_interaction	interactions[MAX_INTERACTIONS];
	t_level_header			header;

	ft_bzero(&export, sizeof(export));
	ft_bzero(&player, sizeof(player));
	ft_bzero(&objects, sizeof(objects));
	ft_bzero(&interactions, sizeof(interactions));
	ft_bzero(&header, sizeof(header));
	counter = 0;
	export = (t_export_sector *)ft_memalloc(sizeof(t_export_sector));
	if (!export)
		exit_error(MSG_ERROR_ALLOC);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	header.sector_count = ft_lstlen(app->sectors);
	header.interaction_count = app->interaction_count;
	header.object_count = app->object_count;
	header.version = FILE_VERSION;
	if (write(fd, &header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	tmp = app->sectors;
	while (counter++ < header.sector_count)
	{
		write_sector(app, tmp, export);
		if (write(fd, export, sizeof(t_export_sector)) == -1)
			exit_error(MSG_ERROR_FILE_WRITE);
		tmp = tmp->next;
	}
	write_player(app, &player);
 	if (write(fd, &player, sizeof(t_export_player)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	write_objects(app, (t_export_object *)&objects);
 	if (write(fd, objects, sizeof(t_export_object) * MAX_OBJECTS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	write_interactions(app, (t_export_interaction *)&interactions);
	if (write(fd, interactions, sizeof(t_export_interaction) * MAX_INTERACTIONS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	free(export);
	/* export_surface(&header, EXPORT_PANELS, fd, PANELS_PATH);
	export_surface(&header, EXPORT_SKYBOX, fd, SKYBOX_PATH);
	export_surface(&header, EXPORT_FONT, fd, FONT_PATH);
	export_surface(&header, EXPORT_UI_FRAME, fd, UI_FRAME_PATH);
	export_surface(&header, EXPORT_TITLESCREEN, fd, TITLESCREEN_PATH);
	export_surface(&header, EXPORT_CROSSHAIR, fd, CROSSHAIR_PATH);
	export_surface(&header, EXPORT_POINTER, fd, POINTER_PATH);
	export_surface(&header, EXPORT_SHIELD, fd, SHIELD_PATH);
	export_surface(&header, EXPORT_HP, fd, HP_PATH);
	export_surface(&header, EXPORT_PISTOL, fd, PISTOL_PATH);
	export_surface(&header, EXPORT_BULLET, fd, BULLET_PATH);
	export_surface(&header, EXPORT_METER, fd, METER_PATH);
	export_surface(&header, EXPORT_PICKUP, fd, PICKUP_PATH);
	export_surface(&header, EXPORT_OBJECT, fd, OBJECT_PATH);
	export_surface(&header, EXPORT_OBJECT_ICON, fd, OBJECT_ICON_PATH);
	export_surface(&header, EXPORT_MONSTER_1, fd, MONSTER_1_PATH);
	export_surface(&header, EXPORT_MONSTER_2, fd, MONSTER_2_PATH);
	export_surface(&header, EXPORT_SPRITE, fd, SPRITE_PATH);
	rle_compress(path); */
	close(fd);
	return (0);
}
