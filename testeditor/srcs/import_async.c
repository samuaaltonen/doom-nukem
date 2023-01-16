/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_async.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:51:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 22:26:48 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Updates progress for the main thread.
 * 
 * @param app 
 * @param thread 
 * @param progress 
 */
void	import_set_complete(t_import_info *info)
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
void	uncompression_update_progress(t_import_info *info)
{
	static int	last_update;

	if (info->uncompressed - last_update > MIN_UNCOMPRESS_UPDATE
		|| info->uncompressed == info->compressed_length)
	{
		if (pthread_mutex_lock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		if (info->uncompressed > 0)
			((t_app *)info->thread->app)->import_progress
				= (double)(info->uncompressed - 1)
				/ (double)info->compressed_length;
		if (pthread_mutex_unlock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		last_update = info->uncompressed;
	}
}

/**
 * @brief Asynchronous function to be used in parallel to the main thread for
 * importing data from level file.
 * 
 * @param data 
 * @return void* 
 */
void	*async_load(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	import_level(app, thread, FILE_PATH);
	pthread_exit(NULL);
}

/**
 * @brief Creates thread for data importing and monitors/renders its progress
 * with loading screen.
 * 
 * @param app 
 */
void	import_file(t_app *app)
{
	t_thread_data	thread;

	thread.app = app;
	app->import_progress = 0.0;
	if (pthread_mutex_init(&thread.lock, NULL)
		|| pthread_create(&thread.thread, NULL, async_load, (void *)(&thread)))
		exit_error(MSG_ERROR_THREADS);
	while (TRUE)
	{
		if (pthread_mutex_lock(&thread.lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		if (app->import_progress == -1.0)
		{
			if (pthread_mutex_unlock(&thread.lock))
				exit_error(MSG_ERROR_THREADS_MUTEX);
			break ;
		}
		render_loading(app, TRUE);
		if (pthread_mutex_unlock(&thread.lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		SDL_Delay(1);
	}
	render_loading(app, TRUE);
}
