/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/24 15:27:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Initializes import level file name.
 * 
 * @param app 
 * @param level 
 */
void	import_init(t_app *app, const char *level)
{
	int	i;
	int	level_number;

	i = 0;
	while (level[i])
	{
		if (level[i] < '0' || level[i] > '9')
			exit_error(MSG_ERROR_LEVEL_NUMBER);
		i++;
	}
	level_number = ft_atoi(level);
	if (level_number < 0 || level_number > MAX_LEVEL)
		exit_error(MSG_ERROR_LEVEL_NUMBER);
	ft_bzero((t_uint8 *)&app->filename, FILE_NAME_LENGTH);
	ft_memcpy((t_uint8 *)&app->filename, LEVEL_IDENTIFIER,
		ft_strlen(LEVEL_IDENTIFIER));
	ft_memcpy((t_uint8 *)&app->filename + ft_strlen(LEVEL_IDENTIFIER), level,
		ft_strlen(level));
}

/**
 * @brief Imports all data from level file.
 * 
 * @param app 
 * @param thread 
 * @param path 
 */
void	import_level(t_app *app, t_thread_data *thread)
{
	t_import_info	info;

	info.data = NULL;
	info.thread = thread;
	rle_uncompress_data(&info, app->filename, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) > (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	app->gravity = (double)info.header.gravity;
	if (app->gravity < MIN_GRAVITY || app->gravity > MAX_GRAVITY)
		app->gravity = DEFAULT_GRAVITY;
	app->interaction_count = 0;
	app->object_count = info.header.object_count;
	import_sectors(app, &info);
	import_player(app, &info);
	import_objects(app, &info);
	import_interactions(app, &info);
	relink_sectors(app);
	app->imported = TRUE;
	free(info.data);
	import_set_complete(&info);
}
