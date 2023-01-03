/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_activate_interaction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:18:12 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/01/03 15:36:55 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Checks if mouse click is on arrow and updates current object interaction 
 * with the next/previous one if it exists.
*/
static t_bool	current_object_interaction(t_app *app, t_point screen_pos,
																		int id)
{
	if (check_mouse(screen_pos, (t_rect){25, 210, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_object_interaction(app,
					app->interaction_count, 0)];
		id = find_object_interaction(app, find_interaction(app) - 1, 0);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	if (check_mouse(screen_pos, (t_rect){255, 210, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_object_interaction(app, 0, 1)];
		id = find_object_interaction(app, find_interaction(app) + 1, 1);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	return (TRUE);
}

/**
 * Checks if mouse click is on arrow and updates current decor interaction 
 * with the next/previous one if it exists.
*/
static t_bool	current_decor_interaction(t_app *app, t_point screen_pos,
																		int id)
{
	if (check_mouse(screen_pos, (t_rect){25, 220, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_decor_interaction(app,
					app->interaction_count, 0)];
		id = find_decor_interaction(app, find_interaction(app) - 1, 0);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	if (check_mouse(screen_pos, (t_rect){255, 220, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_decor_interaction(app, 0, 1)];
		id = find_decor_interaction(app, find_interaction(app) + 1, 1);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	return (TRUE);
}

/**
 * Checks if mouse click is on arrow and updates current sector interaction 
 * with the next/previous one if it exists.
*/
static t_bool	current_sector_interaction(t_app *app, t_point screen_pos,
																		int id)
{
	if (check_mouse(screen_pos, (t_rect){25, 600, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_sector_interaction(app,
					app->interaction_count, 0)];
		id = find_sector_interaction(app, find_interaction(app) - 1, 0);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	if (check_mouse(screen_pos, (t_rect){255, 600, 15, 15}))
	{
		if (!app->current_interaction)
			app->current_interaction
				= &app->interactions[find_sector_interaction(app, 0, 1)];
		id = find_sector_interaction(app, find_interaction(app) + 1, 1);
		if (id < 0)
			return (FALSE);
		app->current_interaction = &app->interactions[id];
		return (FALSE);
	}
	return (TRUE);
}

/**
 * Checks if mouse click is within the add/edit interaction button and either
 * opens the menu for new interaction or menu for the current one.
*/
static void	open_interaction_menu(t_app *app, t_point screen_pos)
{
	if ((check_mouse(screen_pos, (t_rect){42, 228, 190, 16})
		&& app->object_menu) || (check_mouse(screen_pos, (t_rect){42, 238, 190,
		16}) && app->active) || (check_mouse(screen_pos, (t_rect){42, 618, 190,
		16}) && app->active_sector))
	{
		if (!app->current_interaction)
			link_interaction(app);
		app->interaction_menu = TRUE;
	}
	if ((check_mouse(screen_pos, (t_rect){42, 248, 190, 16})
		&& app->object_menu) || (check_mouse(screen_pos, (t_rect){42, 258, 200,
		20}) && app->active) || (check_mouse(screen_pos, (t_rect){42, 638, 190,
		16}) && app->active_sector))
	{
		app->current_interaction = NULL;
		link_interaction(app);
		app->interaction_menu = TRUE;
	}
}

/**
 * Mouse click event to activate interaction menu. Checks if click is within
 * the button and finds the right interaction from the array to make changes
 * to.
*/
void	activate_interaction_menu(t_app *app, t_point screen_pos)
{
	int		id;

	if (app->object_menu && !current_object_interaction(app, screen_pos, 0))
		return ;
	if (app->active && !app->object_menu
		&& !current_decor_interaction(app, screen_pos, 0))
		return ;
	if (!app->active && app->active_sector
		&& !current_sector_interaction(app, screen_pos, 0))
		return ;
	if (!app->current_interaction && app->object_menu)
		id = find_object_interaction(app, 0, 1);
	else if (!app->current_interaction && app->active)
		id = find_decor_interaction(app, 0, 1);
	else if (!app->current_interaction && app->active_sector)
		id = find_sector_interaction(app, 0, 1);
	else
		id = find_interaction(app);
	if (id < 0)
		app->current_interaction = NULL;
	else
		app->current_interaction = &app->interactions[id];
	open_interaction_menu(app, screen_pos);
}
