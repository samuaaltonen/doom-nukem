/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/24 13:03:38 by saaltone         ###   ########.fr       */
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

	if (!threads_created)
	{
		threads_init(app, (t_thread_data *)&threads_data);
		threads_create((t_thread_data *)&threads_data, sector_render_thread);
		threads_created = TRUE;
	}
	ft_bzero(app->occlusion_top, WIN_W * sizeof(int));
	ft_bzero(app->occlusion_bottom, WIN_W * sizeof(int));
	app->overwrite_buffer_count = 0;
	sector_visible_walls(app);
	threads_work((t_thread_data *)&threads_data);
	app->depthmap_fill_switch = !app->depthmap_fill_switch;
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
		sector_stack_render(app, thread,
			app->sectors[app->player.current_sector].stack_index, (t_limit){
			0, WIN_W - 1});
		sector_sky_render(app, thread);
		thread->has_work = FALSE;
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(NULL);
	}
	pthread_exit(NULL);
}

/**
 * @brief Copies occlusion array values.
 * 
 * @param source 
 * @param target 
 */
static void	copy_occlusion(int *source, int *target)
{
	int	i;

	i = 0;
	while (i < WIN_W)
	{
		target[i] = source[i];
		i++;
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
	int		temp_occlusion_top[WIN_W];
	int		temp_occlusion_bottom[WIN_W];
	t_wall	*wall;
	int		i;

	i = 0;
	while (i < app->wallstack.wall_count[stack_id])
	{
		wall = &app->wallstack.walls[stack_id][i];
		sector_walls_raycast(app, thread, wall, limit, app->occlusion_top, app->occlusion_bottom);
		if (app->sectors[wall->sector_id].wall_textures[wall->wall_id]
			== PARTIALLY_TRANSPARENT_PORTAL_TEXTURE_ID)
		{
			copy_occlusion(app->occlusion_top, (int *)&temp_occlusion_top);
			copy_occlusion(app->occlusion_bottom, (int *)&temp_occlusion_bottom);
		}
		if (wall->is_portal && wall->is_inside && !wall->is_member
			&& app->sectors[wall->wall_type].stack_index > stack_id)
				sector_stack_render(app, thread,
					app->sectors[wall->wall_type].stack_index,
					(t_limit){
					ft_max(wall->start_x, limit.start),
					ft_min(wall->end_x, limit.end)
				});
		if (app->sectors[wall->sector_id].wall_textures[wall->wall_id]
			== PARTIALLY_TRANSPARENT_PORTAL_TEXTURE_ID)
			sector_walls_raycast_transparent(app, thread, wall, limit,
				(int *)&temp_occlusion_top, (int *)&temp_occlusion_bottom);
		i++;
	}
}
