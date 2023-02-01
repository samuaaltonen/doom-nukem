/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_activate_interaction_decor.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:18:12 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/01 17:35:21 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks if mouse click is on arrow and updates current decor
 * interaction with the next/previous one if it exists.
 * 
 * @param app
 * @param mouse
 * @param id
 * @return t_bool
*/
t_bool	current_decor_interaction(t_app *app, t_point mouse, int id)
{
	if (check_mouse(mouse, (t_rect){25, 220, 15, 15}))
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
	if (check_mouse(mouse, (t_rect){255, 220, 15, 15}))
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
