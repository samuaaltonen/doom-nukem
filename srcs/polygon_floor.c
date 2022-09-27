/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygon_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:10:45 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/27 22:11:01 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/* static void	apply_height_difference(t_app *app, t_polygon *polygon, int x,
	t_bool is_ceiling)
{
	double	height_difference;

	if (is_ceiling)
		height_difference = polygon->top - app->player.height;
	else
		height_difference = polygon->bottom - app->player.height;
	if (polygon->hits[x].distance_first)
		polygon->hits[x].distance_first = sqrt(
			polygon->hits[x].distance_first* polygon->hits[x].distance_first
			+ height_difference * height_difference);
	if (polygon->hits[x].distance_second)
		polygon->hits[x].distance_second = sqrt(
			polygon->hits[x].distance_second * polygon->hits[x].distance_second
			+ height_difference * height_difference);
} */

static void	polygon_floor_line(t_app *app, t_polygon *polygon, int x, t_bool is_ceiling)
{
	int		start;
	int		end;
	double	distance_start;
	double	distance_step;

	if (is_ceiling)
	{
		start = polygon->hits[x].y_first_top;
		end = polygon->hits[x].y_second_top;
		if (!polygon->hits[x].distance_second
			&& app->player.height >= polygon->top)
				end = WIN_H - 1;
	}
	else
	{
		start = polygon->hits[x].y_first_bottom;
		end = polygon->hits[x].y_second_bottom;
		if (!polygon->hits[x].distance_second
			&& app->player.height >= polygon->bottom)
				end = WIN_H - 1;
	}
	// If 2nd y spot distance is 0 (means there was no 2nd spot), apply distance to camera plane from player (1)
	if (!is_ceiling && !polygon->hits[x].distance_second)
		polygon->hits[x].distance_second = 1.f;
	//apply_height_difference(app, polygon, x, is_ceiling);
	distance_start = polygon->hits[x].distance_first;
	distance_step = fabs(polygon->hits[x].distance_first - polygon->hits[x].distance_second);
	distance_step /= (double)ft_abs(start - end);
	while (start != end)
	{
		put_pixel_to_image_check(app, (t_point){x, start},
			0xFFFFFF,
			distance_start);
		if (start < end)
			start++;
		else
			start--;
		if (distance_start < polygon->hits[x].distance_second)
			distance_start += distance_step;
		else
			distance_start -= distance_step;
	}
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
		if (polygon->hits[x].y_first_top)
			polygon_floor_line(app, polygon, x, TRUE);
		if (polygon->hits[x].y_first_bottom)
			polygon_floor_line(app, polygon, x, FALSE);
	}
}