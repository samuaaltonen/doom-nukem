/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/02 14:51:47 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool in_range(t_app *app, t_vector2 obj_pos, int epsilon)
{

	if (app->player.pos.x > obj_pos.x - epsilon
		&& app->player.pos.x < obj_pos.x + epsilon 
		&& app->player.pos.y > obj_pos.y - epsilon
		&& app->player.pos.y < obj_pos.y + epsilon)
		return (TRUE);
	return (FALSE);
}

static object_hit(t_app *app, int object_id)
{
	
}

int	object_collision(t_app *app, t_vector2 pos, double elev)
{
	int	i;

	i = -1;
	while (app->objects[++i].type > 0)
	{
		if (in_range(app, app->objects[i].position, 2))
		{
			if (ft_point_distance(app->player.pos, app->objects[i].position) < 0.5f)
				object_hit(app, i);
		}
	}
}