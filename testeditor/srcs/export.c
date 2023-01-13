/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:51:54 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/13 15:08:30 by saaltone         ###   ########.fr       */
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
 * @brief Opens or creates a file at path, writes map data to it
 * 
 * @param app 
 * @param path 
 * @return int 
 */
int	export_file(t_app *app, char *path)
{
	int						fd;
	t_level_header			header;

	ft_bzero(&header, sizeof(header));
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
	export_objects(app, fd);
	export_interactions(app, fd);
	export_surfaces(&header, fd);
	export_wavs(&header, fd);
	export_texts(&header, fd);
	close(fd);
	update_header(&header, path);
	rle_compress(path);
	return (0);
}
