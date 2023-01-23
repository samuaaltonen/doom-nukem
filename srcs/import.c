/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:29:44 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/23 16:55:14 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Initializes import level file name.
 * 
 * @param app 
 * @param level 
 */
void	import_init(t_app *app, const char *level)
{
	int	level_number;

	ft_bzero((t_uint8 *)&app->filename, FILE_NAME_LENGTH);
	
	if (!level)
	{
		ft_memcpy((t_uint8 *)&app->filename, DEFAULT_LEVEL,
			ft_strlen(DEFAULT_LEVEL));
		return ;
	}
	level_number = ft_atoi(level);
	if (level_number < 0 || level_number > MAX_LEVEL)
		exit_error(MSG_ERROR_LEVEL_NUMBER);
	ft_memcpy((t_uint8 *)&app->filename, LEVEL_IDENTIFIER,
		ft_strlen(LEVEL_IDENTIFIER));
	ft_memcpy((t_uint8 *)&app->filename + ft_strlen(LEVEL_IDENTIFIER), level,
		ft_strlen(level));
}

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
static void	import_set_complete(t_import_info *info)
{
	if (pthread_mutex_lock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	((t_app *)info->thread->app)->import_progress = -1.0;
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
void	import_update_progress(t_import_info *info)
{
	if (pthread_mutex_lock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	if (info->imported == info->length)
		((t_app *)info->thread->app)->import_progress = 1.0;
	else
		((t_app *)info->thread->app)->import_progress
			= 0.5 + (double)info->imported / (double)info->length * 0.5;
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
			= (double)info->uncompressed / (double)info->compressed_length
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
void	import_level(t_app *app, t_thread_data *thread)
{
	t_import_info		info;

	info.data = NULL;
	info.thread = thread;
	rle_uncompress_data(&info, app->filename, &info.data, &info.length);
	if (!info.data
		|| sizeof(t_level_header) >= (size_t)(info.length))
		exit_error(MSG_ERROR_IMPORT);
	ft_memcpy(&info.header, info.data, sizeof(t_level_header));
	app->gravity = (double)info.header.gravity;
	if (app->gravity < MIN_GRAVITY || app->gravity > MAX_GRAVITY)
		app->gravity = DEFAULT_GRAVITY;
	info.imported = sizeof(t_level_header);
	import_update_progress(&info);
	import_sectors(app, &info);
	import_player(app, &info);
	import_objects(app, &info);
	import_interactions(app, &info);
	import_assets(app, &info);
	free(info.data);
	import_set_complete(&info);
}
