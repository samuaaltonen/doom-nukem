/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:42:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/20 15:40:34 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Compares movement target position with wall endpoints and also to the
 * distance with closest point on wall.
 * 
 * @param app 
 * @param wall 
 * @return t_bool 
 */
static t_bool	collision_possible(t_app *app, t_line wall)
{
	t_vector2	intersection;

	intersection = ft_closest_point(app->player.move_pos, wall);
	return ((ft_point_distance(intersection, app->player.move_pos)
			< COLLISION_OFFSET
		&& ft_point_on_segment(wall, intersection))
		|| ft_point_distance(app->player.move_pos, wall.a) < COLLISION_OFFSET
		|| ft_point_distance(app->player.move_pos, wall.b) < COLLISION_OFFSET);
}

/**
 * @brief If there is a collision, calculates collision position on movement
 * line. Also checks if collision is on the other side of the wall (i.e. when
 * FPS is very low and movement speed high) and sets collision cancel direction
 * accordingly.
 * 
 * @param app 
 * @param wall 
 * @param collision 
 * @return t_bool 
 */
static t_bool	get_collision(t_app *app, t_line wall, t_vector2 *collision)
{
	t_vector2	cancel;
	t_vector2	line_intersection;
	t_vector2	on_wall;

	if (!ft_line_intersection((t_line){app->player.pos, app->player.move_pos},
			wall, &line_intersection))
		return (FALSE);
	on_wall = ft_closest_point(app->player.move_pos, wall);
	cancel = ft_vector_resize(ft_vector2_sub(app->player.move_pos, on_wall),
		COLLISION_OFFSET + MOVE_MIN);
	if (ft_line_side(wall, ft_vector2_add(on_wall, cancel))
		== ft_line_side(wall, app->player.pos))
		*collision = ft_vector2_add(on_wall, cancel);
	else
		*collision = ft_vector2_sub(on_wall, cancel);
	return (TRUE);
}

/**
 * @brief Checks collision on wall endpoints and calculates backtracking change.
 * 
 * @param app 
 * @param wall 
 * @param collision_pos 
 * @return t_vector2 
 */
/* static t_vector2	collision_on_endpoint(t_app *app, t_line wall, t_vector2 collision_pos)
{
	t_vector2	endpoint_nearest;
	double		endpoint_backtrack;
	double		endpoint_distance;
	t_vector2	endpoint_vector;

	if (ft_point_distance(collision_pos, wall.a)
		< ft_point_distance(collision_pos, wall.b))
	{
		endpoint_nearest = ft_closest_point(wall.a, (t_line){app->player.pos,
				app->player.move_pos});
		endpoint_distance = ft_point_distance(wall.a, endpoint_nearest);
	}
	else
	{
		endpoint_nearest = ft_closest_point(wall.b, (t_line){app->player.pos,
				app->player.move_pos});
		endpoint_distance = ft_point_distance(wall.b, endpoint_nearest);
	}
	endpoint_backtrack = sqrt(COLLISION_OFFSET * COLLISION_OFFSET - (endpoint_distance * endpoint_distance));
	//ft_printf("normalized movepoint x%f,y%f, endpoint_nearest x%f,y%f, backtrack dist %f ", app->player.move_pos.x, app->player.move_pos.y, endpoint_nearest.x, endpoint_nearest.y, endpoint_backtrack);
	app->player.move_pos = ft_vector2_sub(app->player.move_vector, ft_vector2_sub(app->player.move_pos, endpoint_nearest));
	endpoint_vector = ft_vector_resize(app->player.move_pos, ft_vector_length(app->player.move_pos) - endpoint_backtrack);
	//ft_printf("endpoint_vector x%f,y%f\n", endpoint_vector.x, endpoint_vector.y);
	return (ft_vector2_add(app->player.pos, endpoint_vector));
} */

/**
 * @brief Checks player collision with a wall. If there is collision, returns
 * TRUE and saves collision point to colpos.
 * 
 * @param app 
 * @param wall 
 * @param position 
 * @return t_bool 
 */
t_bool	circle_collision(t_app *app, t_line wall, t_vector2 *position)
{
	t_vector2	collision;
	t_vector2	collision_on_line;

	if (!collision_possible(app, wall)
		|| !get_collision(app, wall, &collision))
		return (FALSE);
	collision_on_line = ft_closest_point(collision, wall);
	if (ft_point_on_segment(wall, collision_on_line))
	{
		//ft_printf("collision on wall x%f, y%f\n", collision.x, collision.y);
		*position = collision;
		return (TRUE);
	}
	ft_printf("collision on endpoint \n");
		*position = collision;
	/* *position = collision_on_endpoint(app, wall, collision_on_line); */
	return (TRUE);
}
