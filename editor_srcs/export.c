/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/19 17:15:09 by saaltone         ###   ########.fr       */
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
	close(fd);
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
	info.header.sector_count = ft_lstlen(app->sectors);
	info.header.interaction_count = app->interaction_count;
	info.header.object_count = app->object_count;
	info.header.gravity = app->gravity;
	if (write(fd, &info.header, sizeof(t_level_header)) == -1)
		exit_error(MSG_ERROR_FILE_WRITE);
	export_sectors(app, info.header, fd, &info);
	export_player(app, fd, &info);
	export_objects(app, fd, &info);
	export_interactions(app, fd, &info);
	export_surfaces(&info, fd);
	export_wavs(&info, fd);
	export_texts(&info, fd);
	close(fd);
	update_header(&info.header, path);
	rle_compress(&info, path);
	export_set_complete(&info);
}
