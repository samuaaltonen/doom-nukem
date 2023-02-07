/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:39:08 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 18:31:09 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Checks that the given sector has an interaction. Returns 0 (no
 * interaction) if it could not find one and the event id of the first
 * interaction it encountered on the interaction array upon success.
 * 
 * @param app
 * @param id
 * @return int
*/
int	interaction_sector_check(t_app *app, t_sector_list *sector)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{	
		if (!app->interactions[i].activation_wall
			&& app->interactions[i].activation_sector == sector
			&& !app->interactions[i].activation_object)
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}

/**
 * @brief Checks that the given wall has an interaction. Returns 0 (no
 * interaction) if it could not find one and the event id of the first
 * interaction it encountered on the interaction array upon success.
 * 
 * @param app
 * @param id
 * @return int
*/
int	interaction_wall_check(t_app *app, t_wall_list *wall)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{	
		if (app->interactions[i].activation_sector
			&& app->interactions[i].activation_wall == wall)
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}

/**
 * @brief Checks that the given object has an interaction. Returns 0 (no
 * interaction) if it could not find one and the event id of the first
 * interaction it encountered on the interaction array upon success.
 * 
 * @param app
 * @param id
 * @return int
*/
int	interaction_object_check(t_app *app, int id)
{
	int	i;

	i = 0;
	while (i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].activation_object == &app->objects[id])
			return (app->interactions[i].event_id);
		i++;
	}
	return (0);
}
