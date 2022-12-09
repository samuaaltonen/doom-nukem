/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast_decor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:06:55 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/09 14:54:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Sets decor vertical drawing positions.
 * 
 * @param app 
 * @param hit 
 */
static void	set_decor_vertical_positions(t_app *app, t_rayhit *hit)
{
	double		decor_floor;
	double		decor_start;

	decor_floor = (hit->sector->ceil_height - hit->sector->floor_height
			- DECOR_SIZE) / 2 + hit->sector->floor_height
		+ hit->sector->decor_offset[hit->wall_id].y;
	decor_start = WIN_H * app->player.horizon + WIN_H / hit->distance
		* (PLAYER_HEIGHT + app->player.elevation - decor_floor
			- DECOR_SIZE);
	hit->decor_start = (int)decor_start;
	hit->decor_start_actual = decor_start;
	hit->decor_end = hit->decor_start + WIN_H / hit->distance * DECOR_SIZE;
	clamp_int(&hit->decor_start, 0, WIN_H - 1);
	clamp_int(&hit->decor_end, 0, WIN_H - 1);
}

/**
 * @brief Calculates possible wall decoration positions on rayhit.
 * 
 * @param app 
 * @param wall 
 * @param hit 
 * @return t_bool 
 */
t_bool	raycast_decor(t_app *app, t_line wall, t_rayhit *hit)
{
	t_vector2	wall_vector;
	t_line		decor_line;
	double		wall_length;

	if (hit->sector->wall_decor[hit->wall_id] == -1)
		return (FALSE);
	wall_vector = ft_vector2_sub(wall.b, wall.a);
	wall_length = ft_vector_length(wall_vector);
	decor_line.a = ft_vector2_add(wall.a, ft_vector_resize(wall_vector,
				(wall_length - DECOR_SIZE) / 2
				+ hit->sector->decor_offset[hit->wall_id].x));
	decor_line.b = ft_vector2_add(decor_line.a,
			ft_vector_resize(wall_vector, DECOR_SIZE));
	if (!(ft_vector_length(ft_vector2_sub(hit->position, wall.a))
			>= ft_vector_length(ft_vector2_sub(decor_line.a, wall.a))
			&& ft_vector_length(ft_vector2_sub(hit->position, wall.a))
			<= ft_vector_length(ft_vector2_sub(decor_line.b, wall.a))))
		return (FALSE);
	hit->decor_texture = hit->sector->wall_decor[hit->wall_id];
	hit->decor_texture_offset = ft_vector_length(ft_vector2_sub(hit->position,
				decor_line.a));
	set_decor_vertical_positions(app, hit);
	return (TRUE);
}
