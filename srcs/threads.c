/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/14 14:41:11 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Initializes thread information structs.
 * 
 * @param app 
 * @param threads_data 
 */
void	threads_init(t_app *app, t_thread_data *threads_data)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		threads_data[i].app = app;
		threads_data[i].id = i;
		threads_data[i].has_work = FALSE;
		pthread_cond_init(&threads_data[i].cond, NULL);
		pthread_mutex_init(&threads_data[i].lock, NULL);
		i++;
	}
}

/**
 * @brief Creates threads for given function and does not join them to main.
 * These threads are intended to be persistent.
 * 
 * @param app 
 * @param renderer 
 */
void	threads_create(t_thread_data *threads_data, void *(*renderer)(void *))
{
	int			id;

	id = 0;
	while (id < THREAD_COUNT)
	{
		if (pthread_create(&threads_data[id].thread, NULL, renderer,
				(void *)(&threads_data[id])))
			exit_error(MSG_ERROR_THREADS);
		id++;
	}
}

/**
 * @brief Signals threads to awake them and wait until their work is complete.
 * 
 * @param threads_data 
 */
void	threads_work(t_thread_data *threads_data)
{
	int	i;

	i = -1;
	while (++i < THREAD_COUNT)
	{
		threads_data[i].has_work = TRUE;
		pthread_cond_signal(&threads_data[i].cond);
	}
	while (TRUE)
	{
		i = -1;
		while (++i < THREAD_COUNT)
		{
			if (pthread_mutex_trylock(&threads_data[i].lock))
				break ;
			pthread_mutex_unlock(&threads_data[i].lock);
			if (threads_data[i].has_work)
				break ;
		}
		if (i == THREAD_COUNT)
			return ;
	}
}
