/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/07 14:41:03 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

void render_grid(t_app *app)
{
	int x;
	int y;
	x = 0;
	y = 0;

	t_vector2 screen = (t_vector2){0.0,0.0};

	while (y < app->surface->h)
	{
		x = 0;
		while(x < app->surface->w)
		{
			screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
			screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;

			t_vector2 value = (t_vector2){fabs(fmod(screen.x, 1)),fabs(fmod(screen.y, 1))};
			if(value.x > 0.9 || value.y > 0.9 || value.x < 0.1 || value.y < 0.1)
				put_pixel_to_surface(app->surface, x, y, 0x424242);
			x++;
		}
		y++;
	}
			//-50 + ( 0  / 1000) * 100
}
