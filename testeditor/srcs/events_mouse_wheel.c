/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_wheel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 19:07:58 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/16 19:08:19 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Mouse scroll zoom.
 * 
 * @param app 
 * @param event 
 * @return int 
 */
int	events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if (event->wheel.y > 0 && app->zoom_area.x < 200)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
		app->view_pos.x *= 2;
		app->view_pos.y *= 2;
		app->zoom_range += 1;
		app->movement_speed /= 2;
	}	
	else if (event->wheel.y < 0 && app->zoom_area.x > 6)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
		app->view_pos.x /= 2;
		app->view_pos.y /= 2;
		app->zoom_range -= 1;
		app->movement_speed *= 2;
	}
	return (0);
}
