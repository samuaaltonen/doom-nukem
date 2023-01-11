/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/11 20:17:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns line id that matches the wall pointer.
 * 
 * @param list 
 * @param wall 
 * @return int 
 */
int	get_wall_id(t_vec2_lst *list, t_vec2_lst *wall)
{
	int		i;

	if (!wall)
		return (-1);
	i = 0;
	while (wall != list && i < MAX_SEARCH_COUNT)
	{
		i++;
		list = list->next;
	}
	if (i == MAX_SEARCH_COUNT)
		exit_error(MSG_ERROR_LEVEL_DATA);
	return (i);
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
	t_export_interaction	temp;
	int						i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		temp.activation_object = get_object_id(app,app->interactions[i].activation_object);
		temp.activation_sector = get_sector_id(app,app->interactions[i].activation_sector);
		if(temp.activation_sector != -1 && app->interactions[i].activation_wall)
			temp.activation_wall = get_wall_id(app->interactions[i].activation_sector->wall_list, app->interactions[i].activation_wall);
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
	t_export_object			objects[MAX_OBJECTS];
	t_export_interaction	interactions[MAX_INTERACTIONS];
	t_level_header			header;

	ft_bzero(&objects, sizeof(objects));
	ft_bzero(&interactions, sizeof(interactions));
	ft_bzero(&header, sizeof(header));
	counter = 0;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	header.sector_count = ft_lstlen(app->sectors);
	header.interaction_count = app->interaction_count;
	header.object_count = app->object_count;
	header.version = FILE_VERSION;
	if (write(fd, &header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	export_sectors(app, header, fd);
	export_player(app, fd);
	write_objects(app, (t_export_object *)&objects);
 	if (write(fd, objects, sizeof(t_export_object) * MAX_OBJECTS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	write_interactions(app, (t_export_interaction *)&interactions);
	if (write(fd, interactions, sizeof(t_export_interaction) * MAX_INTERACTIONS) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	export_surfaces(&header, fd);
	export_wavs(&header, fd);
	export_texts(&header, fd);
	close(fd);
	fd = open(path, O_WRONLY, 0644);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	if (write(fd, &header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	close(fd);
	rle_compress(path);
	return (0);
}
