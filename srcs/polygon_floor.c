/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:10:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/27 19:50:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	polygon_floor_line(t_app *app, t_polygon *polygon, int x, t_bool is_ceiling)
{
	int		start;
	int		end;
	double	distance_step;

	if (is_ceiling)
	{
		start = polygon->hits[x].y_first_top;
		end = polygon->hits[x].y_second_top;
	}
	else
	{
		start = polygon->hits[x].y_first_bottom;
		end = polygon->hits[x].y_second_bottom;
	}
	distance_step = fabs(polygon->hits[x].distance_first - polygon->hits[x].distance_second);
	distance_step /= (double)ft_abs(start - end);
	while (start != end)
	{
		put_pixel_to_image_check(app, (t_point){x, start},
			start < end ? 0xFFFFFF : 0x00FF00,
			polygon->hits[x].distance_first);
		if (start < end)
			start++;
		else
			start--;
		if (polygon->hits[x].distance_first < polygon->hits[x].distance_second)
			polygon->hits[x].distance_first += distance_step;
		else
			polygon->hits[x].distance_first -= distance_step;
	}
	/* if (x == 500 && polygon->texture == MINECRAFT_GRASS_SIDE) {
		ft_printf("End distance %f, 2nd distance %f\n", polygon->hits[x].distance_first, polygon->hits[x].distance_second);
	} */
}

/** TODO
 * calculate tex_x, tex_y direction vector for texture.
 */

/**
 * Draws polygon floors and ceilings.
*/
void	polygon_draw_floors(t_app *app, t_polygon *polygon)
{
	int	x;

	x = -1;
	while (++x < WIN_W)
	{
		if (!polygon->hits[x].y_first_bottom && !polygon->hits[x].y_first_top
			&& !polygon->hits[x].y_second_bottom && !polygon->hits[x].y_second_top)
			continue ;
		polygon_floor_line(app, polygon, x, TRUE);
	}
}