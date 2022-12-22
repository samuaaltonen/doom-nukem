/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_wall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:42:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 23:38:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if collision is possible. Compares player position and movement
 * position sides relative to wall and also if closest point on wall from
 * movement pois is within wall segment or if movement position is close enough
 * to wall endpoints.
 * 
 * @param start_pos 
 * @param end_pos 
 * @param wall 
 * @param is_member 
 * @return t_bool 
 */
t_bool	collision_possible(t_vector2 start_pos, t_vector2 end_pos,
	t_line wall, t_bool is_member)
{
	t_vector2	intersection;

	if (is_member && !ft_line_side(wall, start_pos))
		return (FALSE);
	intersection = ft_closest_point(end_pos, wall);
	if (ft_point_on_segment(wall, intersection)
		&& ft_line_side(wall, end_pos)
		!= ft_line_side(wall, start_pos))
		return (TRUE);
	if (ft_point_distance(intersection, end_pos)
		< COLLISION_OFFSET && ft_point_on_segment(wall, intersection))
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
 * @brief Checks player collision with a wall. If there is collision, returns
 * TRUE and saves collision point movement position.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @param portal_id 
 * @return t_collision 
 */
t_collision	collision_wall(t_app *app, int sector_id, int wall_id,
	int portal_id)
{
	t_line				wall;

	wall = get_wall_line(app, sector_id, wall_id);
	if (!collision_possible(app->player.pos, app->player.move_pos,
			wall, sector_id == portal_id))
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
	app->player.collisions[app->player.total_collisions] = wall;
	app->player.total_collisions++;
	return (COLLISION_WALL);
}
