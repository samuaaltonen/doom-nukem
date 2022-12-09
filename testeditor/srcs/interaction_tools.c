/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:21:08 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/12/07 15:21:11 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Loops through the interaction array to find the id of the current
 * interaction. Returns the array id and in case of error -1.
*/
int	find_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (&(app->interactions[index]) == app->current_interaction)
			return (index);
		index++;
	}
	return (-1);
}

/**
 * Loops through the interaction array to find if the active wall's decor
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_decor_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_wall == app->active
			&& app->interactions[index].activation_sector == app->active_sector)
			return (index);
		index++;
	}
	return (-1);
}

/**
 * Loops through the interaction array to find if the current sector
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_sector_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_sector == app->active_sector
			&& !app->interactions[index].activation_wall
			&& !app->interactions[index].activation_object)
			return (index);
		index++;
	}
	return (-1);
}

/**
 * Loops through the interaction array to find if the current object
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
*/
int	find_object_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index <= app->interaction_count)
	{
		if (app->interactions[index].activation_object == app->current_object)
			return (index);
		index++;
	}
	return (-1);
}
