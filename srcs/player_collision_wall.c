/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_wall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:42:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 17:01:06 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if collision is possible. Compares player position and movement
 * position sides relative to wall and also if closest point on wall from
 * movement pois is within wall segment or if movement position is close enough
 * to wall endpoints.
 * 
 * @param app 
 * @param wall 
 * @return t_bool 
 */
static t_bool	collision_possible(t_app *app, t_line wall)
{
	t_vector2	intersection;

	intersection = ft_closest_point(app->player.move_pos, wall);
	if (ft_point_on_segment(wall, intersection)
		&& ft_line_side(wall, app->player.move_pos)
		!= ft_line_side(wall, app->player.pos))
		return (TRUE);
	if (ft_point_distance(intersection, app->player.move_pos)
		< COLLISION_OFFSET && ft_point_on_segment(wall, intersection))
		return (TRUE);
	if (ft_point_distance(app->player.move_pos, wall.a) < COLLISION_OFFSET
		|| ft_point_distance(app->player.move_pos, wall.b) < COLLISION_OFFSET)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Calculates possible movement point based on preferred point and side.
 * 
 * @param wall 
 * @param coord 
 * @param side 
 * @return t_vector2 
 */
t_vector2	get_possible_movement_point(t_line wall, t_vector2 coord, int side)
{
	t_vector2	cancel;
	t_vector2	on_wall;

	on_wall = ft_closest_point(coord, wall);
	cancel = ft_vector_resize(ft_vector2_sub(coord, on_wall),
			COLLISION_OFFSET + MOVE_MIN);
	if (ft_line_side(wall, ft_vector2_add(on_wall, cancel)) == side)
		return (ft_vector2_add(on_wall, cancel));
	return (ft_vector2_sub(on_wall, cancel));
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
	t_vector2	line_intersection;

	if (!ft_line_intersection((t_line){app->player.pos, app->player.move_pos},
		wall, &line_intersection))
		return (FALSE);
	*collision = get_possible_movement_point(wall, app->player.move_pos,
		ft_line_side(wall, app->player.pos));
	return (TRUE);
}

/**
 * @brief Checks player collision with a wall. If there is collision, returns
 * TRUE and saves collision point movement position.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @param portal_id 
 * @return t_collision 
 */
t_collision_type	collision_wall(t_app *app, int sector_id, int wall_id,
	int portal_id)
{
	t_line		wall;
	t_vector2	collision;
	t_vector2	collision_on_line;

	wall = get_wall_line(app, sector_id, wall_id);
	if (!collision_possible(app, wall) || !get_collision(app, wall, &collision))
		return (COLLISION_NONE);
	if (portal_id != -1 && app->sectors[sector_id].wall_textures[wall_id]
		!= PARTIALLY_TRANSPARENT_TEXTURE_ID
		&& portal_can_enter(app, wall, app->player.current_sector, portal_id))
		return (COLLISION_PORTAL);
	if (app->player.total_collisions >= MAX_CONCURRENT_COLLISIONS - 1)
	{
		app->player.move_pos = app->player.pos;
		app->player.total_collisions = 0;
		return (COLLISION_WALL);
	}
	collision_on_line = ft_closest_point(collision, wall);
	app->player.collisions[app->player.total_collisions] = (t_collision){wall,
		collision};
	app->player.total_collisions++;

	if (ft_point_on_segment(wall, collision_on_line))
	{
		
		//app->player.move_pos = collision;
		return (COLLISION_WALL);
	}
	//app->player.move_pos = collision;
	return (COLLISION_WALL);
}
