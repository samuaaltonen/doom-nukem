/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_activate_interaction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:18:12 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/01 17:37:40 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks if mouse click is within the add/edit interaction button and
 * either opens the menu for new interaction or menu for the current one.
 * 
 * @param app
 * @param mouse
*/
static void	open_interaction_menu(t_app *app, t_point mouse)
{
	if ((check_mouse(mouse, (t_rect){42, 228, 190, 16})
		&& app->object_menu) || (check_mouse(mouse, (t_rect){42, 238, 190,
		16}) && app->active) || (check_mouse(mouse, (t_rect){42, 618, 190,
		16}) && app->active_sector))
	{
		if (!app->current_interaction)
			link_interaction(app);
		app->interaction_menu = TRUE;
	}
	if ((check_mouse(mouse, (t_rect){42, 248, 190, 16})
		&& app->object_menu) || (check_mouse(mouse, (t_rect){42, 258, 200,
		20}) && app->active) || (check_mouse(mouse, (t_rect){42, 638, 190,
		16}) && app->active_sector))
	{
		app->current_interaction = NULL;
		link_interaction(app);
		app->interaction_menu = TRUE;
	}
}

/**
 * @brief Finds and sets current interaction.
 * 
 * @param app 
 */
static void	find_current_interaction(t_app *app)
{
	int		id;

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
}

/**
 * @brief Mouse click event to activate interaction menu. Checks if click is
 * within the button and finds the right interaction from the array to make
 * changes to.
 * 
 * @param app
 * @param mouse
*/
void	activate_interaction_menu(t_app *app, t_point mouse)
{
	if (app->active && check_mouse(mouse, (t_rect){90, 160, 100, 21})
		&& app->active->decor == -1)
		app->active->decor = 0;
	else if (app->active && check_mouse(mouse, (t_rect){185, 120, 80, 21})
		&& app->active->decor > -1)
	{
		app->active->decor = -1;
		del_all_decor_interactions(app);
	}
	if (app->object_menu && !current_object_interaction(app, mouse, 0))
		return ;
	if (app->active && !app->object_menu
		&& !current_decor_interaction(app, mouse, 0))
		return ;
	if (!app->active && app->active_sector
		&& !current_sector_interaction(app, mouse, 0))
		return ;
	find_current_interaction(app);
	open_interaction_menu(app, mouse);
}
