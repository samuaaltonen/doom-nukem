/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/13 14:48:03 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Calculates the closest point to snap to.
 * 
 * @param snap_pos
 * @param world_pos
 * @param divider
*/
static void	snap_to_point(double *snap_pos, double *world_pos, double divider)
{
	double	tmp;

	tmp = fabs(fmod(*world_pos, divider));
	if (tmp < (divider / 2))
	{
		if (*world_pos < 0)
			*snap_pos = *world_pos + tmp;
		else
			*snap_pos = *world_pos - tmp;
	}
	else
	{
		if (*world_pos < 0)
			*snap_pos = *world_pos - (divider - tmp);
		else
			*snap_pos = *world_pos + (divider - tmp);
	}
}

/**
 * @brief Converts mouse position to world space and snaps it to the closest
 * grid position.
 * 
 * @param app
 * @param mouse
 * @param snap_pos
 * @param divider
 */
void	snap_to_nearest(t_app *app, t_point *mouse, t_vector2 *snap_pos,
																double divider)
{
	t_vector2	world_pos;

	world_pos = screen_to_world(app, *mouse);
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	snap_to_point(&snap_pos->x, &world_pos.x, divider);
	snap_to_point(&snap_pos->y, &world_pos.y, divider);
}

/**
 * @brief Events for mouse tracking.
 * 
 * @param app
 * @return int
 */
int	events_mouse_track(t_app *app)
{
	t_point	mouse;

	SDL_GetMouseState(&mouse.x, &mouse.y);
	snap_to_nearest(app, &mouse, &app->mouse_track, app->divider);
	if (app->mouse_down && app->player_menu
		&& check_mouse(mouse, (t_rect){40, 185, 240, 20}))
			app->player.armor = mouse.x - 40;
	if (app->mouse_down && app->player_menu
		&& check_mouse(mouse, (t_rect){40, 245, 240, 20}))
			app->player.health = mouse.x - 40;
	if (app->player_menu && check_mouse(mouse, (t_rect){40, 60, 32, 32}))
		app->player.selected_weapon = 0;
	if (app->player_menu && check_mouse(mouse, (t_rect){82, 60, 32, 32}))
		app->player.selected_weapon = 1;
	if (app->player_menu && check_mouse(mouse, (t_rect){124, 60, 32, 32}))
		app->player.selected_weapon = 2;
	if (app->player_menu && check_mouse(mouse, (t_rect){166, 60, 32, 32}))
		app->player.selected_weapon = 3;
	if (app->player_menu && check_mouse(mouse, (t_rect){208, 60, 32, 32}))
		app->player.selected_weapon = 4;
	return (0);
}

/**
 * @brief Zoom event for mouse scroll.
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

/**
 * @brief Dispatches SDL2 event to event handler functions.
 * 
 * @param app
 * @param event
 * @return int
*/
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return (events_window_destroy());
	if (event->type == SDL_KEYUP)
		return (events_keyup(app, event->key.keysym.sym));
	if (event->type == SDL_KEYDOWN)
		return (events_keydown(app, event->key.keysym.sym));
	if (event->type == SDL_MOUSEMOTION)
		return (events_mouse_track(app));
	if (event->type == SDL_MOUSEWHEEL)
		return (events_mouse_wheel(app, event));
	if (event->type == SDL_MOUSEBUTTONUP)
		return (events_mouse_click(app, event));
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return (events_mouse_drag(app));
	return (0);
}
