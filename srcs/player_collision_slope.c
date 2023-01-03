/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_slope.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:28:47 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/03 17:02:56 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks slop collision to prevent the player entering into slope that
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

	if (!app->sectors[sector_id].floor_slope_magnitude
		&& !app->sectors[sector_id].ceil_slope_magnitude)
		return ;
	if (app->sectors[sector_id].floor_slope_magnitude)
		slope = ft_vector2_sub(app->sectors[sector_id].floor_slope_end,
				app->sectors[sector_id].floor_slope_start);
	else
		slope = ft_vector2_sub(app->sectors[sector_id].ceil_slope_end,
				app->sectors[sector_id].ceil_slope_start);
	collision_position = ft_vector2_add(app->player.move_pos,
			ft_vec2_mult(ft_vector2_normalize(slope), COLLISION_OFFSET));
	if (sector_ceil_height(app, sector_id, collision_position)
		- sector_floor_height(app, sector_id, collision_position)
		>= app->player.height + COLLISION_CEIL)
		return ;
	collision_line = ft_line_resize((t_line){app->player.move_pos,
			ft_vector2_add(app->player.move_pos,
				ft_vector_perpendicular(slope))}, MAX_LINE_LENGTH, EXTEND_BOTH);
	app->player.collisions[app->player.total_collisions] = collision_line;
	app->player.total_collisions++;
}
