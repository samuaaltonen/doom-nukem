/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:32:45 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/18 22:32:48 by saaltone         ###   ########.fr       */
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
		if (pthread_cond_init(&threads_data[i].cond, NULL))
			exit_error(NULL);
		if (pthread_mutex_init(&threads_data[i].lock, NULL))
			exit_error(NULL);
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
	int		id;

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
 * @brief Sets thread as done.
 * 
 * @param thread 
 */
void	thread_set_done(t_thread_data *thread)
{
	if (pthread_mutex_lock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	thread->has_work = FALSE;
	if (pthread_mutex_unlock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
}

/**
 * @brief Checks if thread is done working.
 * 
 * @param thread 
 * @return t_bool 
 */
t_bool	thread_check_done(t_thread_data *thread)
{
	t_bool	has_work;

	if (pthread_mutex_lock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	has_work = thread->has_work;
	if (pthread_mutex_unlock(&thread->lock))
		exit_error(MSG_ERROR_THREADS_MUTEX);
	return (has_work);
}

/**
 * @brief Signals threads to awake them and wait until their work is complete.
 * If there is still some thread working, waits 1ms before checking it again.
 * 
 * @param threads_data 
 */
void	threads_work(t_thread_data *threads_data)
{
	int	check_count;
	int	i;

	i = -1;
	while (++i < THREAD_COUNT)
	{
		if (pthread_mutex_lock(&threads_data[i].lock))
			exit_error(MSG_ERROR_THREADS_SIGNAL);
		threads_data[i].has_work = TRUE;
		if (pthread_mutex_unlock(&threads_data[i].lock)
			|| pthread_cond_signal(&threads_data[i].cond))
			exit_error(MSG_ERROR_THREADS_SIGNAL);
	}
	i = -1;
	check_count = -1;
	while (++i < THREAD_COUNT && ++check_count < THREAD_DEADLOCK_CHECK)
	{
		if (thread_check_done(&threads_data[i]))
			i = -1;
	}
}
