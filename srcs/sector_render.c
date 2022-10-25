/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/25 15:02:59 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws current sector where player is in
 */
void	render_sectors(t_app *app)
{
	// Zero occlusion arrays
	ft_bzero(app->occlusion_top, WIN_W * sizeof(int));
	ft_bzero(app->occlusion_bottom, WIN_W * sizeof(int));

	/**
	 * Get possible visible walls (this can be moved to player position update 
	 * function (not needed to calculate possible visible walls every frame if 
	 * there is no movement))
	 */
	sector_visible_walls(app);

	/** 
	 * Calculates translated x positions in window space
	 * - makes ordering faster since no need to check order of walls that have
	 *   no x overlap in window
	 * - these values are used also in rendering part
	 */
	//sector_walls_prepare(app, (t_wall *)&app->visible_walls, app->visible_walls_count);

	/**
	 * Order visible walls
	*/
	//sector_walls_order(app, (t_wall *)&app->visible_walls, app->visible_walls_count);

	/**
	 * Render sectors
	*/
	render_multithreading(app, sector_walls_render);
}

/**
 * Multithreaded renderer for sector walls.
*/
void	*sector_walls_render(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	int	i = 0;
	/* ft_printf("--- NEW FRAME ---\n"); */
	while (i < app->visible_walls_count)
	{
		/* ft_printf("%d:%d\n", app->visible_walls[i].sector_id, app->visible_walls[i].wall_id); */
		sector_walls_raycast(app, thread, &app->visible_walls[i]);
		i++;
	}
	pthread_exit(NULL);
}
