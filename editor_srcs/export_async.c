/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_async.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:44:12 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/17 16:06:44 by saaltone         ###   ########.fr       */
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
void	export_set_complete(t_import_info *info)
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
void	export_update_progress(t_import_info *info)
{
	if (pthread_mutex_lock(&info->thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	if (info->imported == info->length)
		((t_app *)info->thread->app)->import_progress = 1.0;
	else
		((t_app *)info->thread->app)->import_progress
			= (double)info->imported / (double)info->length;
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
void	compression_update_progress(t_import_info *info)
{
	static int	last_update;

	if (((t_app *)info->thread->app)->import_progress == 0.5)
		last_update = 0;
	if (info->uncompressed - last_update > MIN_UNCOMPRESS_UPDATE
		|| info->uncompressed == info->compressed_length)
	{
		if (pthread_mutex_lock(&info->thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		((t_app *)info->thread->app)->import_progress
			= 0.5 + (double)info->uncompressed
			/ (double)info->compressed_length * 0.5;
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
void	*async_save(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	export_level(app, thread, FILE_PATH);
	pthread_exit(NULL);
}

/**
 * @brief Creates thread for data importing and monitors/renders its progress
 * with loading screen.
 * 
 * @param app 
 */
void	export_file(t_app *app)
{
	t_thread_data	thread;

	thread.app = app;
	app->import_progress = 0.0;
	if (pthread_mutex_init(&thread.lock, NULL)
		|| pthread_create(&thread.thread, NULL, async_save, (void *)(&thread)))
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
		render_loading(app, FALSE);
		if (pthread_mutex_unlock(&thread.lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		SDL_Delay(1);
	}
	render_loading(app, FALSE);
}
