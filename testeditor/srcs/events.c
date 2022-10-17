/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:36:52 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/17 14:34:54 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * converts mouse_pos to world space and snaps to grid
 */
void	snap_to_nearest(t_app *app, t_point *mouse_pos, t_vector2 *snap_pos, double divider)
{
	t_vector2	world_pos;
	double		tmp;

	world_pos.x = app->view_pos.x + (mouse_pos->x / (double)app->surface->w) * app->zoom_area.x;
	world_pos.y = app->view_pos.y + (mouse_pos->y / (double)app->surface->h) * app->zoom_area.y;
	snap_pos->x = world_pos.x;
	snap_pos->y = world_pos.y;
	tmp = fabs(fmod(world_pos.x, divider));
	if(tmp < (divider / 2))
	{
		if(world_pos.x < 0)
			snap_pos->x = world_pos.x + tmp;
		else
			snap_pos->x = world_pos.x - tmp;
	}
	else
	{
		if(world_pos.x < 0)
			snap_pos->x = world_pos.x - (divider - tmp);
		else
			snap_pos->x = world_pos.x + (divider - tmp);
	}
	tmp = fabs(fmod(world_pos.y, divider));
	if(tmp < (divider / 2))
	{
		if(world_pos.y < 0)
			snap_pos->y = world_pos.y + tmp;
		else
			snap_pos->y = world_pos.y - tmp;
	}
	else
	{
		if(world_pos.y < 0)
			snap_pos->y = world_pos.y - (divider - tmp);
		else
			snap_pos->y = world_pos.y + (divider - tmp);
	}
}

/**
 * Tracks mouse position and saves the snapped location to t_app
 */
int	events_mouse_track(t_app *app)
{
	t_point	current_pos;
	
	SDL_GetMouseState(&current_pos.x, &current_pos.y);		
	snap_to_nearest(app, &current_pos, &app->mouse_click, app->divider);
	ft_printf("x=%f, y=%f modes:c%i,o%i\n",app->mouse_click.x, app->mouse_click.y, app->list_creation, app->list_ongoing);
	if(app->active_sector)
		ft_printf("inside = %i\n", app->active_sector->id);
	return (0);
}


/**
 * loops through all points in all sectors to find matchin coordinates
 * // future add checking only within active sector
 */
t_vec2list	*find_clicked_vector(t_app *app)
{
	t_vec2list		*found;
	if(app->active_sector)
	{
		found = app->active_sector->wall_list;
		while(found)
		{
			if(app->mouse_click.x == found->point.x && app->mouse_click.y == found->point.y)
				return(found);
			if(found->next == app->active_sector->wall_list)
				break;
			found = found->next;
		}
	}
	return(NULL);
}

/**
 * if not in sector creation, select points
 * else add new points to list or starts a new list
 */
int	events_mouse_click(t_app *app, SDL_Event *event)
{
	t_vec2list *tmp;

	if(event->button.button == SDL_BUTTON_LEFT && !app->list_ongoing && app->list_creation)
	{
		app->active = new_vector_list(&app->mouse_click);
		app->active_last = app->active;
		app->list_ongoing = TRUE;
	}
	else if(event->button.button == SDL_BUTTON_LEFT && app->list_ongoing)
	{

		if(app->mouse_click.x == app->active->point.x && app->mouse_click.y == app->active->point.y)
		{
			return (complete_sector(app));
		}
		else if(valid_point(app))
		{
			tmp = new_vector_list(&app->mouse_click);
			put_to_vector_list(&app->active, tmp);
			app->active_last = tmp;
		}
	}
	else if(event->button.button == SDL_BUTTON_LEFT)
	{
		//if active sector has member sectors find them before vertexes
		
		if(app->active_sector)
			app->active = find_clicked_vector(app);
		else
			app->active_sector = click_sector(app);

	}
	else
	{
		app->active = NULL;
		app->active_sector = NULL;
	}
	return (0);
}


/**
 * Mouse scroll zoom
 */
int events_mouse_wheel(t_app *app, SDL_Event *event)
{
	if(event->wheel.y > 0 && app->zoom_area.x < 200)
	{
		app->zoom_area.x *= 2;
		app->zoom_area.y *= 2;
		app->view_pos.x *= 2;
		app->view_pos.y *= 2;
		app->zoom_range += 1;
	}	
	else if(event->wheel.y < 0 && app->zoom_area.x > 6)
	{
		app->zoom_area.x /= 2;
		app->zoom_area.y /= 2;
		app->view_pos.x /= 2;
		app->view_pos.y /= 2;
		app->zoom_range -= 1;
	}
	return (0);
}

/**
 * Dispatches SDL2 event to event handler functions.
*/
int	dispatch_event(t_app *app, SDL_Event *event)
{
	if (event->type == SDL_QUIT)
		return events_window_destroy();
	if (event->type == SDL_KEYUP)
		return events_keyup(event->key.keysym.sym, app);
	if (event->type == SDL_KEYDOWN)
		return events_keydown(event->key.keysym.sym, app);
	if (event->type == SDL_MOUSEMOTION)
		return events_mouse_track(app);
	if (event->type == SDL_MOUSEWHEEL)
		return events_mouse_wheel(app, event);	
	if (event->type == SDL_MOUSEBUTTONUP)
		return events_mouse_click(app, event);
	return (0);
}
