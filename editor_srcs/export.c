/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/01 17:41:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Initializes export header.
 * 
 * @param app 
 * @param header 
 */
static void	initialize_export_header(t_app *app, t_level_header *header)
{
	header->sector_count = ft_lstlen(app->sectors);
	header->interaction_count = app->interaction_count;
	header->object_count = app->object_count;
	header->gravity = (int)app->gravity;
}

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

/**
 * @brief Updates header info to file.
 * 
 * @param header 
 * @param path 
 */
void	update_header(t_level_header *header, char *path)
{
	int	fd;

	fd = open(path, O_WRONLY, 0644);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	if (write(fd, header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	if (close(fd) < 0)
		exit_error(MSG_ERROR_FILE_CLOSE);
}

/**
 * @brief Exports all data to level file.
 * 
 * @param app 
 * @param thread 
 * @param path 
 */
void	export_level(t_app *app, t_thread_data *thread, char *path)
{
	t_import_info	info;
	int				fd;

	ft_bzero(&info, sizeof(t_import_info));
	info.thread = thread;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit_error(MSG_ERROR_FILE_OPEN);
	initialize_export_header(app, &info.header);
	if (write(fd, &info.header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	export_sectors(app, info.header, fd, &info);
	export_player(app, fd, &info);
	export_objects(app, fd, &info);
	export_interactions(app, fd, &info);
	if (app->export_assets)
		export_assets(&info, fd);
	if (close(fd) < 0)
		exit_error(MSG_ERROR_FILE_CLOSE);
	update_header(&info.header, path);
	rle_compress(&info, path);
	export_set_complete(&info);
}
