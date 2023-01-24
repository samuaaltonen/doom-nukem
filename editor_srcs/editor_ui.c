/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:09:02 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/19 18:24:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Draws the zoom slider to the right side of the screen.
 * 
 * @param app
*/
void	zoom_slider(t_app *app)
{
	int		x;
	int		y;
	int		zoom_point;

	y = app->surface->h / 4;
	zoom_point = y + (app->surface->h / 2) / 6 * app->zoom_range;
	render_up_and_down_arrows(app, (t_point){app->surface->w - 33, y - 13},
		(t_point){app->surface->w - 33, app->surface->h - (app->surface->h / 4)
		+ 10}, 16);
	while (y <= (app->surface->h - (app->surface->h / 4) + 10))
	{
		x = app->surface->w - 30;
		while (x <= (app->surface->w - 20))
		{
			if (x == (app->surface->w - 25) || y == app->surface->h / 4
				|| y == (app->surface->h - (app->surface->h / 4) + 10))
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (y >= zoom_point && y <= zoom_point + 10)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
}

/**
 * @brief Changes mouse_down state to true when mouse button left is
 * pressed down.
 * 
 * @param app
 * @return int
*/
int	events_mouse_drag(t_app *app)
{
	app->mouse_down = TRUE;
	return (0);
}

/**
 * @brief Changes divider count for the background grid.
 * 
 * @param app
 * @param keycode
*/
void	move_divider(t_app *app, SDL_Keycode keycode)
{
	if (keycode == SDLK_z && app->divider > 0.2f)
		app->divider /= 2;
	else if (keycode == SDLK_x && app->divider < 0.75f)
		app->divider *= 2;
}

/**
 * @brief Creates a floor/ceiling slope from the active point to the furthest 
 * point in sector upon keypress.
 * 
 * @param app
 * @param keycode
*/
void	activate_slope(t_app *app, SDL_Keycode keycode)
{
	if (keycode == SDLK_y && app->active_sector && app->active)
	{
		app->active_sector->ceil_slope_wall = app->active;
		app->active_sector->ceil_slope_opposite
			= find_opposite_point(app->active_sector, app->active);
	}
	if (keycode == SDLK_h && app->active_sector && app->active)
	{
		app->active_sector->floor_slope_wall = app->active;
		app->active_sector->floor_slope_opposite
			= find_opposite_point(app->active_sector, app->active);
	}
}
