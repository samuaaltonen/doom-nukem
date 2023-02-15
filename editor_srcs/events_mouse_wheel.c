/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_wheel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:07:58 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/15 15:23:57 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Zoom event for mouse scroll.
 * 
 * @param app
 * @param event
 * @return int
 */
int	events_mouse_wheel(t_app *app, SDL_Event *event)
{
	double	zoom;

	zoom = 1.f;
	if (event->wheel.y < 0 && app->zoom_range < 6)
	{
		zoom = 0.5f;
		app->view_size = ft_vec2_mult(app->view_size, 2.f);
		app->zoom_range += 1;
		app->movement_speed *= 0.5f;
	}	
	else if (event->wheel.y > 0 && app->zoom_range > 1)
	{
		zoom = 2.f;
		app->view_size = ft_vec2_mult(app->view_size, 0.5f);
		app->zoom_range -= 1;
		app->movement_speed *= 2;
	}
	if (event->wheel.y != 0)
	{
		app->view_start.x = (app->view_start.x - app->mouse_track.x)
			/ zoom + app->mouse_track.x;
		app->view_start.y = (app->view_start.y - app->mouse_track.y)
			/ zoom + app->mouse_track.y;
	}
	return (0);
}
