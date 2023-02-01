/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_circle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/01 17:50:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Midpoint Circle Algorithm, calculates only one octant
 * 3 - 2 * rad avoids overdraw -rad works as well
 * 4 / 6 and 4 / 10 make the circle more circular
 * 
 * @param app
 * @param pos
 * @param rad
 * @param color
 */
void	draw_circle(t_app *app, t_point pos, int rad, int color)
{
	t_point	tmp;
	int		err;

	tmp.x = 0;
	tmp.y = rad;
	err = 3 - 2 * rad;
	while (tmp.x <= tmp.y)
	{
		put_pixel_to_surface(app->surface, pos.x + tmp.x, pos.y + tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.y, pos.y + tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.x, pos.y + tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.y, pos.y + tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.x, pos.y - tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.y, pos.y - tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.x, pos.y - tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.y, pos.y - tmp.x, color);
		if (err < 0)
			err += 4 * tmp.x + 6;
		else
		{
			err += 4 * (tmp.x - tmp.y) + 10;
			tmp.y--;
		}
		tmp.x++;
	}
}
