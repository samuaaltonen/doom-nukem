/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:02:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/06 15:15:30 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Left mouse click events when list creation is toggled on. Creates a
 * linked list from the clicked points, checking that their position is valid
 * and completes the drawn sector.
 * 
 * @param app
 * @return int
*/
static int	list_creation_events(t_app *app)
{
	t_vec2_lst	*tmp;

	if (!app->list_ongoing)
	{
		app->active = new_vector_list(&app->mouse_track);
		app->active_last = app->active;
		app->list_ongoing = TRUE;
	}
	else
	{
		if (app->active && app->mouse_track.x == app->active->point.x
			&& app->mouse_track.y == app->active->point.y && valid_sector(app))
			return (complete_sector(app));
		else if (valid_point(app) && app->active)
		{
			tmp = new_vector_list(&app->mouse_track);
			put_to_vector_list(&app->active, tmp);
			app->active_last = tmp;
		}
	}
	return (0);
}

/**
 * @brief Left mouse click events when there's an active sector. If player edit
 * mode is toggled on, places player on map. If object is clicked, selcts object
 * and changes menu to object menu. Clicking member sectors selects them as
 * active sector.
 * 
 * @param app
*/
static void	active_sector_events(t_app *app)
{
	if (app->player_edit)
	{
		app->player.position = app->mouse_track;
		app->player.direction = (t_vector2){0.f, 1.f};
		app->player.sector = app->active_sector;
		app->player_edit = FALSE;
		check_player_position(app);
	}
	else if (select_object(app))
		app->object_menu = TRUE;
	else if (app->active_sector && app->active_sector->member_sectors[0]
		&& find_child_sector(app))
		app->active_sector = find_child_sector(app);
	app->active = find_clicked_vector(app);
}

/**
 * @brief Left mouse click events for the small menu on the upper right corner.
 * 
 * @param app
 * @param mouse
*/
static void	rightside_menu_events(t_app *app, t_point mouse)
{
	if (check_mouse(mouse, (t_rect){WIN_W - 155, 10, 150, 20}))
	{
		if ((app->active_sector && get_member_sector_count(app->active_sector)
				< MAX_MEMBER_SECTORS) || (!app->active_sector)
			|| (app->active_sector && app->active_sector->parent_sector))
			app->list_creation = ft_toggle(app->list_creation);
		if (app->list_ongoing)
			cancel_list_creation(app);
	}
	if (check_mouse(mouse, (t_rect){WIN_W - 155, 40, 150, 20}))
		app->linking_mode = ft_toggle(app->linking_mode);
	if (check_mouse(mouse, (t_rect){WIN_W - 155, 70, 150, 20})
		&& app->active_sector && app->object_count < MAX_OBJECTS)
		toggle_new_object(app, app->object_new);
	if (check_mouse(mouse, (t_rect){WIN_W - 155, 100, 150, 20}) && app->sectors)
	{
		app->export_assets = FALSE;
		export_file(app);
	}
	if (check_mouse(mouse, (t_rect){WIN_W - 155, 130, 150, 21}) && app->sectors)
	{
		app->export_assets = TRUE;
		export_file(app);
	}
}

/**
 * @brief All the events happening from left mouse click.
 * 
 * @param app
 * @param mouse
 * @return int
*/
static int	left_click_events(t_app *app, t_point mouse)
{
	if (check_mouse(mouse, (t_rect){WIN_W - 160, 10, 150, 140}))
		rightside_menu_events(app, mouse);
	else if (app->list_creation)
		return (list_creation_events(app));
	else if (app->object_new)
	{
		if (valid_object(app))
			new_object(app);
		app->object_new = FALSE;
	}
	else if (app->player_menu)
		player_menu_events(app, mouse);
	else if (app->interaction_menu && app->current_interaction)
		interaction_menu_events(app, 40, mouse);
	else if (!app->active_sector && app->mouse_track.x == app->player.position.x
		&& app->mouse_track.y == app->player.position.y)
		app->player_menu = TRUE;
	else if (check_mouse(mouse, (t_rect){0, 0, HELP_MENU_W, WIN_H})
		&& !app->interaction_menu)
		activate_interaction_menu(app, mouse);
	else if (app->active_sector)
		active_sector_events(app);
	else
		app->active_sector = click_sector(app);
	return (0);
}

/**
 * @brief All events happening from mouse button up.
 * 
 * @param app
 * @param event
 * @return int
 */
int	events_mouse_click(t_app *app, SDL_Event *event)
{
	t_point		mouse;

	app->mouse_down = FALSE;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (event->button.button == SDL_BUTTON_LEFT)
		return (left_click_events(app, mouse));
	else
	{
		if (app->list_ongoing)
			cancel_list_creation(app);
		if (app->interaction_menu)
			link_interaction(app);
		toggle_new_object(app, TRUE);
		app->active = NULL;
		app->player_menu = FALSE;
		app->object_menu = FALSE;
		if (app->active_sector)
			app->active_sector = app->active_sector->parent_sector;
		else
			app->active_sector = NULL;
	}
	return (0);
}
