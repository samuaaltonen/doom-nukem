/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:23:28 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/14 00:17:20 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws floor.
 */
void	draw_floor(t_app *app, int x, int y_start, int y_end)
{
	/**
	 * Check BOTTOM occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_bottom[x] > WIN_H - y_end)
		y_end = WIN_H - app->occlusion_bottom[x];
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_bottom[x] = WIN_H - y_start;
	/**
	 * TODO: TEXTURES
	 * Draw vertical line
	 */
	while (y_start < y_end)
	{
		put_pixel_to_surface(app->surface, x, y_start, 0xcccccc);
		y_start++;
	}
}
