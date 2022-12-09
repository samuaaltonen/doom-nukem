/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:42:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/09 15:33:30 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

t_bool circle_collision(t_app *app, t_line wall, t_vector2 *colpos)
{
	t_vector2	line_intersection;
	t_vector2	new_intersection;
	t_vector2	move_point;
	move_point = ft_vector2_add(app->player.pos,app->player.move_vector);
	t_line move_line = (t_line){app->player.pos, move_point};
	t_vector2 collision;
	t_vector2 posofcollision;
	t_vector2 pos3;
	t_vector2 endpoint_nearest;
	double endpoint_backtrack;
	double	endpoint_distance;
	t_vector2 endpoint_vector;

	new_intersection = ft_closest_point(move_point, wall);
	if (!ft_line_intersection(move_line, wall, &line_intersection))
		return (FALSE);
	if((ft_point_distance(new_intersection, move_point) < COLLISION_OFFSET && ft_line_segment_point(wall, new_intersection))
		|| (ft_point_distance(move_point, wall.a) < COLLISION_OFFSET)
		|| (ft_point_distance(move_point, wall.b) < COLLISION_OFFSET))
	{
		collision = ft_vector2_sub(line_intersection, ft_vec2_mult(ft_vector_resize(app->player.move_vector, 1.f),
				(ft_point_distance(line_intersection, app->player.pos)
				/ ft_point_distance(ft_closest_point(app->player.pos, wall), app->player.pos)) * COLLISION_OFFSET));
		posofcollision = ft_closest_point(collision, wall);
		pos3 = ft_vector2_add(collision, (ft_vector2_sub(ft_closest_point(app->player.pos, wall), posofcollision)));
		if(ft_line_segment_point(wall, posofcollision))
		{
			ft_printf("collision on wall x%f, y%f\n", collision.x, collision.y);
			*colpos = collision;
			return (TRUE);
		}
		else
		{
			ft_printf("collision on endpoint \n");
			if(ft_point_distance(posofcollision, wall.a) < ft_point_distance(posofcollision, wall.b))
			{
				endpoint_nearest = ft_closest_point(wall.a, move_line);
				endpoint_distance = ft_point_distance (wall.a, endpoint_nearest);
			}
			else
			{
				endpoint_nearest = ft_closest_point(wall.b, move_line);
				endpoint_distance = ft_point_distance (wall.b, endpoint_nearest);
			}
			endpoint_backtrack = sqrt(COLLISION_OFFSET * COLLISION_OFFSET - (endpoint_distance * endpoint_distance));
			ft_printf("normalized movepoint x%f,y%f, endpoint_nearest x%f,y%f, backtrack dist %f ", move_point.x, move_point.y, endpoint_nearest.x, endpoint_nearest.y, endpoint_backtrack);
			move_point = ft_vector2_sub(app->player.move_vector, ft_vector2_sub(move_point, endpoint_nearest));
			endpoint_vector = ft_vector_resize(move_point, ft_vector_length(move_point) - endpoint_backtrack);
			ft_printf("endpoint_vector x%f,y%f\n", endpoint_vector.x, endpoint_vector.y);
			*colpos = ft_vector2_add(app->player.pos, endpoint_vector);
			return (TRUE);
		}
	}
	return (FALSE);
}