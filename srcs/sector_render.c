/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:47:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 15:24:02 by saaltone         ###   ########.fr       */
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

	/** Get possible visible walls (this can be moved to player position update 
	 * function (not needed to calculate possible visible walls every frame if 
	 * there is no movement))
	 * 
	 * Oordered based on distance (closest first) */
	sector_walls_possible_visible(app);

	/* ft_printf("--- new frame ---\n"); */
	int	i = 0;
	while (i < app->possible_visible_count)
	{
		/* if (app->possible_visible[i].is_member)
			ft_printf("Drawing wall at sector %d, wall %d, is_member %d\n",
				app->possible_visible[i].sector_id, 
				app->possible_visible[i].wall_id,
				app->possible_visible[i].is_member); */
		sector_wall_draw(app, app->possible_visible[i].sector_id, app->possible_visible[i].wall_id);
		i++;
	}
}
