/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:53:03 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/06 16:58:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Get the sky pixel color.
 * 
 * @param app 
 * @param x 
 * @param y 
 * @return int 
 */
int	get_sky_pixel(t_app *app, int x, int y)
{
	t_vector2	texture_pos;

	texture_pos.x = (x + app->sky.start.x) * app->sky.pixel_step.x;
	texture_pos.y = (y - app->sky.start.y) * app->sky.pixel_step.y;
	if (texture_pos.x < 0.0)
		texture_pos.x += app->sky.size.x * app->sky.pixel_step.x;
	if (texture_pos.x >= (double)SKYBOX_W)
		texture_pos.x = fmod(texture_pos.x, (double)SKYBOX_W);
	if (texture_pos.y < 0.0)
		texture_pos.y += app->sky.size.y * app->sky.pixel_step.y;
	return (get_pixel_color(app->assets.bg,
			(int)texture_pos.x,
			(int)texture_pos.y));
}
