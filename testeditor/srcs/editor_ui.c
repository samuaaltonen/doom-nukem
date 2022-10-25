/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:09:02 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/24 15:33:36 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void	zoom_slider(t_app *app)
{
	int		x;
	int		y;
	int		zoom_point;

	y = app->surface->h / 4;
	zoom_point = y + (app->surface->h / 2) / 6 * app->zoom_range;
	while (y <= (app->surface->h - (app->surface->h / 4) + 10))
	{
		x = app->surface->w - 30;
		while (x <= (app->surface->w - 20))
		{
			if (x == (app->surface->w - 25) || y == app->surface->h / 4 || y == (app->surface->h - (app->surface->h / 4) + 10))
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			if (y >= zoom_point && y <= zoom_point + 10)
				put_pixel_to_surface(app->surface, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	move_divider(t_app *app, SDL_Keycode keycode)
{
	if (keycode == SDLK_z && app->divider > 0.2f)
		app->divider /= 2;
	else if (keycode == SDLK_x && app->divider < 0.75f)
		app->divider *= 2;
}