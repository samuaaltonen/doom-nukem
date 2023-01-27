/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:47:01 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/26 16:40:55 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool	sector_height(t_app *app, t_bullet *bullet,
		t_bool compare, double (*sector_function)(t_app *, int, t_vector2))
{
	t_vector2	end;
	t_vector2	heights;
	double		end_z;
	double		dist;

	heights.x = sector_function(app, bullet->sector, bullet->start);
	heights.y = sector_function(app, bullet->sector, bullet->end);
	dist = ft_point_distance(bullet->start, bullet->end);
	end_z = bullet->start_z + dist * bullet->end_z;
	if ((heights.y < end_z && compare) || (!compare && heights.y > end_z))
	{
		if (ft_line_intersection((t_line){(t_vector2){0.f, bullet->start_z},
			(t_vector2){dist, end_z}}, (t_line){(t_vector2){0.f, heights.x},
			(t_vector2){dist, heights.y}}, &heights))
		{
			end = ft_vector2_add(bullet->start, ft_vector_resize(
						ft_vector2_sub(bullet->end, bullet->start), heights.x));
			if (inside_sector(app, bullet->sector, end))
			{
				bullet->end = end;
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

t_bool	sector_height_collision(t_app *app, t_bullet *bullet)
{
	if (sector_height(app, bullet, TRUE, sector_ceil_height)
		+ sector_height(app, bullet, FALSE, sector_floor_height))
		return (FALSE);
	return (TRUE);
}
