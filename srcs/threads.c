/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/11 14:40:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Renders the current view of the player with multithreading.
*/
void	render_multithreading(t_app *app, void *(*renderer)(void *))
{
	int			id;
	pthread_t	thread_identifiers[THREAD_COUNT];

	id = 0;
	while (id < THREAD_COUNT)
	{
		if (pthread_create(&thread_identifiers[id], NULL, renderer,
				(void *)(&(app->thread_info)[id])))
			exit_error(MSG_ERROR_THREADS);
		id++;
	}
	id = 0;
	while (id < THREAD_COUNT)
	{
		if (pthread_join(thread_identifiers[id], NULL) != 0)
			exit_error(MSG_ERROR_THREADS_JOIN);
		id++;
	}
}

/**
 * @brief Creates threads for given function and does not join them to main.
 * These threads are intended to be persistent.
 * 
 * @param app 
 * @param renderer 
 */
void	persistent_multithreading(t_app *app, void *(*renderer)(void *))
{
	int			id;

	id = 0;
	while (id < THREAD_COUNT)
	{
		if (pthread_create(&app->thread_info[id].thread, NULL, renderer,
				(void *)(&app->thread_info[id])))
			exit_error(MSG_ERROR_THREADS);
		id++;
	}
}
