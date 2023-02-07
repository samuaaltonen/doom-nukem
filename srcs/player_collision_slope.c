/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_slope.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:28:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 17:58:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns slope direction vector sum of a sector.
 * 
 * @param app 
 * @param sector_id 
 * @return t_vector2 
 */
static t_vector2	get_sector_slope_direction(t_app *app, int sector_id)
{
	t_vector2	floor_slope;
	t_vector2	ceil_slope;

	if (app->sectors[sector_id].floor_slope_magnitude)
		floor_slope = ft_vector2_sub(app->sectors[sector_id].floor_slope_end,
				app->sectors[sector_id].floor_slope_start);
	if (app->sectors[sector_id].ceil_slope_magnitude)
		ceil_slope = ft_vector2_sub(app->sectors[sector_id].ceil_slope_end,
				app->sectors[sector_id].ceil_slope_start);
	if (app->sectors[sector_id].floor_slope_magnitude
		&& app->sectors[sector_id].ceil_slope_magnitude)
	{
		floor_slope = ft_vector_resize(floor_slope,
				fabs(app->sectors[sector_id].floor_slope_magnitude)
				/ ft_vector_length(floor_slope));
		ceil_slope = ft_vector_resize(ceil_slope,
				fabs(app->sectors[sector_id].ceil_slope_magnitude)
				/ ft_vector_length(ceil_slope));
		return (ft_vector2_normalize(ft_vector2_add(ceil_slope, floor_slope)));
	}
	if (app->sectors[sector_id].floor_slope_magnitude)
		return (ft_vector2_normalize(floor_slope));
	return (ft_vector2_normalize(ceil_slope));
}

/**
 * @brief Returns space of given position in a sector.
 * 
 * @param app 
 * @param sector_id 
 * @param position 
 * @return double 
 */
static double	get_position_space(t_app *app, int sector_id,
	t_vector2 position)
{
	return (sector_ceil_height(app, sector_id, position)
		- sector_floor_height(app, sector_id, position));
}

/**
 * @brief Returns optimal position where there is no longer collision with
 * slope sum.
 * 
 * @param app 
 * @param collision_position 
 * @param space 
 * @param space_away 
 * @return t_vector2 
 */
static t_vector2	get_optimal_position(t_app *app,
	t_vector2 collision_position, double space, double space_away)
{
	double	space_distance;
	double	from_collision;

	if (space - space_away == 0.0)
		return (collision_position);
	space_distance = space / (space_away - space);
	from_collision = (space - space_distance / space)
		* (app->player.height + COLLISION_CEIL);
	return (ft_vector2_add(collision_position, ft_vector_resize(
				ft_vector2_sub(collision_position, app->player.move_pos),
				from_collision)));
}

/**
 * @brief Checks slope collision to prevent the player entering into slope that
 * cannot fit the player vertically.
 * 
 * @param app 
 * @param sector_id 
 */
void	collision_slope(t_app *app, int sector_id)
{
	t_line		collision_line;
	t_vector2	collision_position;
	t_vector2	slope;
	double		space;
	double		space_away;

	if (!app->sectors[sector_id].floor_slope_magnitude
		&& !app->sectors[sector_id].ceil_slope_magnitude)
		return ;
	slope = get_sector_slope_direction(app, sector_id);
	collision_position = ft_vector2_add(app->player.move_pos,
			ft_vec2_mult(slope, COLLISION_OFFSET));
	space = get_position_space(app, sector_id, collision_position);
	if (space >= app->player.height + COLLISION_CEIL)
		return ;
	space_away = get_position_space(app, sector_id,
			ft_vector2_sub(collision_position, slope));
	collision_position = get_optimal_position(app, collision_position, space,
			space_away);
	collision_line = ft_line_resize((t_line){collision_position,
			ft_vector2_add(collision_position,
				ft_vector_perpendicular(slope))}, MAX_LINE_LENGTH, EXTEND_BOTH);
	app->player.collisions[app->player.total_collisions] = collision_line;
	app->player.total_collisions++;
}
