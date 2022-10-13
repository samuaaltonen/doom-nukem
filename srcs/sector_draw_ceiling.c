/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_draw_ceiling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:17:22 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/14 00:17:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws ceiling.
 */
void	draw_ceiling(t_app *app, int x, int y_start, int y_end)
{
	/**
	 * Check TOP occlusion and only draw not occluded parts.
	 */
	if (x < 0 || x >= WIN_W)
		return ;
	if (app->occlusion_top[x] > y_start)
		y_start = app->occlusion_top[x] + 1;
	if (y_start == y_end || y_start > y_end)
		return;
	app->occlusion_top[x] = y_end;
	/**
	 * TODO: TEXTURES
	 * Draw vertical line
	 */
	while (y_start < y_end)
	{
		put_pixel_to_surface(app->surface, x, y_start, 0x333333);
		y_start++;
	}
}
