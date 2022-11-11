/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/11 15:02:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws current sector where player is in
 */
void	render_sectors(t_app *app)
{
	static t_bool	persistent_threads_created;
	int				i;

	if (!persistent_threads_created)
	{
		persistent_multithreading(app, sector_render_thread);
		persistent_threads_created = TRUE;
	}

	// Zero occlusion arrays
	ft_bzero(app->occlusion_top, WIN_W * sizeof(int));
	ft_bzero(app->occlusion_bottom, WIN_W * sizeof(int));

	/**
	 * Get possible visible walls for each visible sector (this can be moved to
	 * player position update function (not needed to calculate possible visible
	 * walls every frame if there is no movement))
	 */
	sector_visible_walls(app);

	/**
	 * Render sector stacks
	*/
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_mutex_lock(&app->thread_info[i].lock);
		app->thread_info[i].has_work = TRUE;
		pthread_cond_signal(&app->thread_info[i].cond);
		pthread_mutex_unlock(&app->thread_info[i].lock);
		i++;
	}
	t_bool	all_ready = FALSE;
	while (!all_ready)
	{
		all_ready = TRUE;
		i = 0;
		while (i < THREAD_COUNT)
		{
			pthread_mutex_lock(&app->thread_info[i].lock);
			if (app->thread_info[i].has_work)
				all_ready = FALSE;
			pthread_mutex_unlock(&app->thread_info[i].lock);
			i++;
		}
	}
}

/**
 * Multithreaded renderer for sector walls.
*/
/* void	*sector_render_thread(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	sector_stack_render(app, thread,
		app->sectors[app->player.current_sector].stack_index, 0, WIN_W - 1);
	pthread_exit(NULL);
} */

/**
 * Persistent multithreaded renderer for sector walls.
*/
void	*sector_render_thread(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	while (TRUE)
	{
		pthread_mutex_lock(&thread->lock);
		while (!thread->has_work)
			pthread_cond_wait(&thread->cond, &thread->lock);
		sector_stack_render(app, thread,
			app->sectors[app->player.current_sector].stack_index, 0, WIN_W - 1);
		thread->has_work = FALSE;
		pthread_mutex_unlock(&thread->lock);
	}
	pthread_exit(NULL);
}

/**
 * @brief Renders one sector stack.
 *
 * @param app
 * @param thread
 * @param stack_id
 * @param start_x
 * @param end_x
 */
void	sector_stack_render(t_app *app, t_thread_data *thread, int stack_id, int start_x, int end_x)
{
	t_wall	*wall;
	int		i;

	i = 0;
	while (i < app->wallstack.wall_count[stack_id])
	{
		wall = &app->wallstack.walls[stack_id][i];
		sector_walls_raycast(app, thread, wall, start_x, end_x);
		/**
		 * If wall is a portal recurse into that
		 */
		if (wall->is_portal && wall->is_inside && !wall->is_member)
			sector_stack_render(app, thread,
				app->sectors[wall->wall_type].stack_index,
				ft_max(wall->start_x, start_x),
				ft_min(wall->end_x, end_x));
		i++;
	}
}