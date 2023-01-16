/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 19:08:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

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
 * converts mouse_pos to world space and snaps to grid
 */
void	snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos,
																double divider)
{
	t_vector2	world_pos;

	world_pos = screen_to_world(app, *mouse_pos);
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	snap_to_point(&snap_pos->x, &world_pos.x, divider);
	snap_to_point(&snap_pos->y, &world_pos.y, divider);
}
