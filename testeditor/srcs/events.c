/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 21:54:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Calculates the closest point to snap to.
 * 
 * @param snap_pos
 * @param world_pos
 * @param divider
*/
static void	snap_to_point(double *snap_pos, double *world_pos, double divider)
{
	double	tmp;

	tmp = fabs(fmod(*world_pos, divider));
	if (tmp < (divider / 2))
	{
		if (*world_pos < 0)
			*snap_pos = *world_pos + tmp;
		else
			*snap_pos = *world_pos - tmp;
	}
	else
	{
		if (*world_pos < 0)
			*snap_pos = *world_pos - (divider - tmp);
		else
			*snap_pos = *world_pos + (divider - tmp);
	}
}

/**
 * @brief Converts mouse position to world space and snaps it to the closest
 * grid position.
 * 
 * @param app
 * @param mouse
 * @param snap_pos
 * @param divider
 */
void	snap_to_nearest(t_app *app, t_point *mouse, t_vector2 *snap_pos,
																double divider)
{
	t_vector2	world_pos;

	world_pos = screen_to_world(app, *mouse);
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	snap_to_point(&snap_pos->x, &world_pos.x, divider);
	snap_to_point(&snap_pos->y, &world_pos.y, divider);
}
