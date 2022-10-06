/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 13:54:55 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/10/06 15:27:13 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	open_map_editor(t_app *app)
{
	int			x;
	int			y;

	x = 0;
	while (x < WIN_W)
	{
		y = 0;
		while (y < WIN_H)
		{
			if (x < EDITOR_MENU_W)
				put_pixel_to_surface(app->surface, x, y, EDITOR_MENU_COLOR);
			else
			{
				if ((x % (10 * app->editor.zoom)) == 0
					|| (y % (10 * app->editor.zoom) == 0))
					put_pixel_to_surface(app->surface, x, y, EDITOR_GRID_COLOR);
				else
					put_pixel_to_surface(app->surface, x, y, EDITOR_BG_COLOR);
			}
			y++;
		}
		x++;
	}
}