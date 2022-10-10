/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:03:35 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/10 14:09:23 by ssulkuma         ###   ########.fr       */
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
			if(value.x > 0.95 || value.y > 0.95 || value.x < 0.05 || value.y < 0.05)
				put_pixel_to_surface(app->surface, x, y, 0x252525);
			x++;
		}
		y++;
	}
			//-50 + ( 0  / 1000) * 100
}

//current real time nearest point to cursor
t_vector2 *nearest_point_cursor(t_app *app)
{
(void)app;
 return(NULL);

}

//check if point is already in list
t_bool valid_point(t_app *app)
{
(void)app;
 return(0);

}

//check if point is first element in list and complete sector
t_bool complete_sector(t_app *app)
{
(void)app;
 return(0);

}
