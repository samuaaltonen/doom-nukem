/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/17 17:43:46 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Draws all visible sectors with multithreading. 
 * 1. When called first time, creates threads for rendering.
 * 2. Zeroes occlusion arrays
 * 3. Gathers possibly visible walls from each visible sector
 * 4. Renders walls
 *
 * @param app 
 */
void	render_sectors(t_app *app)
{
	/* static t_thread_data	threads_data[THREAD_COUNT]; */
	static t_bool			threads_created;

	/* if (!threads_created)
	{
		ft_printf("{cyan}DEBUG{reset} Creating threads for sector rendering.\n");
		threads_init(app, (t_thread_data *)&app->threads_data);
		threads_created = TRUE;
	} */
	if (!threads_created)
	{
		//ft_printf("{yellow}DEBUG{reset} Creating threads for sector rendering.\n");
		threads_init(app, (t_thread_data *)&app->threads_data);
		threads_create((t_thread_data *)&app->threads_data, sector_render_thread);
		threads_created = TRUE;
	}
	ft_bzero(app->occlusion_top, WIN_W * sizeof(int));
	ft_bzero(app->occlusion_bottom, WIN_W * sizeof(int));
	//ft_printf("{cyan}DEBUG{reset} Getting walls.\n");
	sector_visible_walls(app);
	threads_work((t_thread_data *)&app->threads_data);
	/* legacy_render_multithreading((t_thread_data *)&app->threads_data, legacy_sector_render_thread); */
}

/**
 * @brief Multithreaded renderer for sector walls.
 * 
 * @param data 
 * @return void* 
 */
void	*sector_render_thread(void *data)
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
		/* if (!thread->has_work)
		{
			if (pthread_mutex_unlock(&thread->lock))
				exit_error(NULL);
			continue ;
		} */
		sector_stack_render(app, thread,
			app->sectors[app->player.current_sector].stack_index, (t_limit){
			0, WIN_W - 1});
		thread->has_work = FALSE;
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(NULL);
	}
	pthread_exit(NULL);
}

void	*legacy_sector_render_thread(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	sector_stack_render(app, thread,
		app->sectors[app->player.current_sector].stack_index, (t_limit){
		0, WIN_W - 1});
	pthread_exit(NULL);
}

/**
 * @brief Renders one sector stacks walls one by one. When portal is
 * encountered, recurses into that.
 *
 * @param app
 * @param thread
 * @param stack_id
 * @param limit
 */
void	sector_stack_render(t_app *app, t_thread_data *thread, int stack_id,
	t_limit limit)
{
	t_wall	*wall;
	int		i;

	i = 0;
	while (i < app->wallstack.wall_count[stack_id])
	{
		wall = &app->wallstack.walls[stack_id][i];
		sector_walls_raycast(app, thread, wall, limit);
		if (wall->is_portal && wall->is_inside && !wall->is_member
			&& app->sectors[wall->wall_type].stack_index > stack_id)
				sector_stack_render(app, thread,
					app->sectors[wall->wall_type].stack_index,
					(t_limit){
					ft_max(wall->start_x, limit.start),
					ft_min(wall->end_x, limit.end)
				});
		i++;
	}
}
