/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/15 15:52:49 by saaltone         ###   ########.fr       */
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
	static t_thread_data	threads_data[THREAD_COUNT];
	static t_bool			threads_created;
	int						i;

	if (!threads_created)
	{
		threads_init(app, (t_thread_data *)&threads_data);
		threads_create((t_thread_data *)&threads_data, sector_render_thread);
		threads_created = TRUE;
	}
	ft_bzero(app->occlusion_top, WIN_W * sizeof(int));
	ft_bzero(app->occlusion_bottom, WIN_W * sizeof(int));
	i = 0;
	while (i < app->sector_count)
	{
		ft_bzero(app->sectors[i].is_visible, sizeof(t_bool) * THREAD_COUNT);
		i++;
	}
	sector_wallstack_build(app);
	threads_work((t_thread_data *)&threads_data);
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
			exit_error(MSG_ERROR_THREADS_MUTEX);
		while (!thread->has_work)
		{
			if (pthread_cond_wait(&thread->cond, &thread->lock))
				exit_error(MSG_ERROR_THREADS_SIGNAL);
		}
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(MSG_ERROR_THREADS_MUTEX);
		sector_stack_render(app, thread,
			app->sectors[app->player.sector].stack_index, (t_limit){
			0, WIN_W - 1});
		thread_set_done(thread);
	}
	pthread_exit(NULL);
}

/**
 * @brief Copies occlusion array values.
 * 
 * @param source 
 * @param target 
 */
static void	copy_occlusion(t_app *app, int **top, int **bottom)
{
	int	i;

	i = 0;
	*top = (int *)malloc(WIN_W * sizeof(int));
	if (!*top)
		exit_error(MSG_ERROR_ALLOC);
	*bottom = (int *)malloc(WIN_W * sizeof(int));
	if (!*bottom)
		exit_error(MSG_ERROR_ALLOC);
	while (i < WIN_W)
	{
		(*bottom)[i] = app->occlusion_bottom[i];
		(*top)[i] = app->occlusion_top[i];
		i++;
	}
}

/**
 * @brief Renders a wall. If wall type is portal, recurses into that sector with
 * sector_stack_render.
 * 
 * @param app 
 * @param thread 
 * @param limit 
 * @param wall 
 */
static void	sector_render_wall(t_app *app, t_thread_data *thread, t_limit limit,
	t_wall *wall)
{
	int	*top;
	int	*bottom;

	sector_walls_raycast(app, thread, (t_raycast_info){wall, limit,
		app->occlusion_top, app->occlusion_bottom});
	if (app->sectors[wall->sector_id].wall_textures[wall->wall_id]
		<= PARTIALLY_TRANSPARENT_TEXTURE_ID)
		copy_occlusion(app, &top, &bottom);
	if (wall->is_portal && wall->is_inside && !wall->is_member
		&& wall->already_passed[thread->id] < MAX_SECTOR_CORNERS)
	{
		wall->already_passed[thread->id]++;
		sector_stack_render(app, thread,
			app->sectors[wall->wall_type].stack_index,
			(t_limit){ft_max(wall->start_x, limit.start),
			ft_min(wall->end_x, limit.end)});
	}
	if (app->sectors[wall->sector_id].wall_textures[wall->wall_id]
		<= PARTIALLY_TRANSPARENT_TEXTURE_ID)
	{
		sector_walls_raycast_transparent(app, thread, (t_raycast_info){
			wall, limit, top, bottom});
		free(top);
		free(bottom);
	}
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
	int		i;

	i = -1;
	while (++i < app->wallstack.wall_count[stack_id])
	{
		sector_render_wall(app, thread, limit,
			&app->wallstack.walls[stack_id][i]);
	}
}
