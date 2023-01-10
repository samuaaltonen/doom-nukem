/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_loading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:51:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/10 13:23:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

# define	IMPORT_WORK_LOAD 123

void	*async_import(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	while (TRUE)
	{
		if (pthread_mutex_lock(&thread->lock))
			exit_error(NULL);
		while (!thread->has_work)
			if (pthread_cond_wait(&thread->cond, &thread->lock))
				exit_error(NULL);
		thread->id++;
		SDL_Delay(10);
		if (thread->id >= IMPORT_WORK_LOAD)
			thread->has_work = FALSE;
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(NULL);
	}
	pthread_exit(NULL);
}

void	app_load(t_app *app)
{
	t_thread_data	thread_data;

	thread_data.app = app;
	thread_data.id = 0;
	thread_data.has_work = TRUE;
	if (pthread_cond_init(&thread_data.cond, NULL)
		|| pthread_mutex_init(&thread_data.lock, NULL)
		|| pthread_create(&thread_data.thread, NULL, async_import,
				(void *)(&thread_data))
		|| pthread_cond_signal(&thread_data.cond)
		|| pthread_mutex_unlock(&thread_data.lock))
		exit_error(MSG_ERROR_THREADS);
	while (TRUE)
	{
		if (pthread_mutex_lock(&thread_data.lock))
			exit_error(MSG_ERROR_THREADS_SIGNAL);
		if (!thread_data.has_work)
		{
			if (pthread_mutex_unlock(&thread_data.lock))
				exit_error(MSG_ERROR_THREADS_SIGNAL);
			break ;
		}
		ft_printf("progress %d\n", thread_data.id);
		if (pthread_mutex_unlock(&thread_data.lock))
			exit_error(MSG_ERROR_THREADS_SIGNAL);
	}
	ft_printf("thread done %d\n", thread_data.id);
}

void	render_loading(t_app *app, int progress)
{
	while (TRUE)
	{
		while (SDL_PollEvent(&app->event))
			dispatch_event(app, &app->event);
		if (!app->conf->toggle_loop)
			render_frame(app);
	}
}