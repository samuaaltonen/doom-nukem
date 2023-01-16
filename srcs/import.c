/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 18:56:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
void	import_update_progress(t_import_info *info)
{
	if (pthread_mutex_lock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	if (info->imported == info->length)
		((t_app *)info->thread->app)->import_progress = 1.0;
	else
		((t_app *)info->thread->app)->import_progress
			= 0.5 + (double) info->imported / (double) info->length * 0.5;
	if (pthread_mutex_unlock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
void	uncompression_update_progress(t_import_info *info)
{
	static int	last_update;

	if (info->uncompressed - last_update > MIN_UNCOMPRESS_UPDATE
		|| info->uncompressed == info->compressed_length)
	{
		if (pthread_mutex_lock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		((t_app *)info->thread->app)->import_progress
			= (double) info->uncompressed / (double) info->compressed_length
			* 0.5;
		if (pthread_mutex_unlock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		last_update = info->uncompressed;
	}
}

/**
 * @brief Imports all data from level file.
 * 
 * @param app 
 * @param thread 
 * @param path 
 */
void	import_level(t_app *app, t_thread_data *thread, char *path)
{
	t_import_info		info;

	info.data = NULL;
	info.thread = thread;
	rle_uncompress_data(&info, path, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) >= (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	info.imported = sizeof(t_level_header);
	import_update_progress(&info);
	import_sectors(app, &info);
	import_player(app, &info);
	import_objects(app, &info);
	import_interactions(app, &info);
	import_assets(app, &info);
	free(info.data);
	info.imported = info.length;
	import_update_progress(&info);
}
