/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:52:39 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/19 17:16:59 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Imports all data from level file.
 * 
 * @param app 
 * @param thread 
 * @param path 
 */
void	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_import_info	info;

	info.data = NULL;
	info.thread = thread;
	rle_uncompress_data(&info, path, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) > (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	app->gravity = info.header.gravity;
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
