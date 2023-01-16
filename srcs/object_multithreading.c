/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_multithreading.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:01:53 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 22:35:40 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	*object_render_thread(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	while (TRUE)
	{
		if (pthread_mutex_lock(&thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		while (!thread->has_work)
		{
			if (pthread_cond_wait(&thread->cond, &thread->lock))
				exit_error(MSG_ERROR_THREADS_SIGNAL);
		}
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		objects_render(app, thread);
		thread_set_done(thread);
	}
	pthread_exit(NULL);
}

void	render_objects(t_app *app)
{
	static t_thread_data	threads_data[THREAD_COUNT];
	static t_bool			threads_created;

	if (!threads_created)
	{
		threads_init(app, (t_thread_data *)&threads_data);
		threads_create((t_thread_data *)&threads_data, object_render_thread);
		threads_created = TRUE;
	}
	objects_visible(app);
	threads_work((t_thread_data *)&threads_data);
}
