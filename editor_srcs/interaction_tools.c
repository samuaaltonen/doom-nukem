/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:21:08 by ssulkuma          #+#    #+#             */
/*   Updated: 2023/02/07 18:30:38 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Loops through the interaction array to find the id of the current
 * interaction. Returns the array id and in case of error -1.
 * 
 * @param app
 * @return int
*/
int	find_interaction(t_app *app)
{
	int		index;

	index = 0;
	while (index < MAX_INTERACTIONS)
	{
		if (&(app->interactions[index]) == app->current_interaction)
			return (index);
		index++;
	}
	return (-1);
}

/**
 * @brief Loops through the interaction array to find if the active wall's decor
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
 * 
 * @param app
 * @param start_id
 * @param direction
 * @return int
*/
int	find_decor_interaction(t_app *app, int start_id, t_bool direction)
{
	int		index;

	if (start_id < 0 && start_id >= MAX_INTERACTIONS)
		return (-1);
	index = start_id;
	if (direction == 1)
	{
		while (index < MAX_INTERACTIONS)
		{
			if (app->interactions[index].activation_wall == app->active
				&& app->interactions[index].activation_sector
				== app->active_sector)
				return (index);
			index++;
		}
		return (-1);
	}
	while (index >= 0 && index < MAX_INTERACTIONS)
	{
		if (app->interactions[index].activation_wall == app->active
			&& app->interactions[index].activation_sector == app->active_sector)
			return (index);
		index--;
	}
	return (-1);
}

/**
 * @brief Loops through the interaction array to find if the current sector
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
 * 
 * @param app
 * @param start_id
 * @param direction
 * @return int
*/
int	find_sector_interaction(t_app *app, int start_id, t_bool direction)
{
	int		index;

	if (start_id < 0 && start_id >= MAX_INTERACTIONS)
		return (-1);
	index = start_id;
	if (direction == 1)
	{
		while (index < MAX_INTERACTIONS)
		{
			if (app->interactions[index].activation_sector == app->active_sector
				&& !app->interactions[index].activation_wall
				&& !app->interactions[index].activation_object)
				return (index);
			index++;
		}
	}
	while (index >= 0 && index < MAX_INTERACTIONS)
	{
		if (app->interactions[index].activation_sector == app->active_sector
			&& !app->interactions[index].activation_wall
			&& !app->interactions[index].activation_object)
			return (index);
		index--;
	}
	return (-1);
}

/**
 * @brief Loops through the interaction array to find if the current object
 * has an interaction or not. Returns array id if it finds one and
 * -1 if not.
 * 
 * @param app
 * @param start_id
 * @param direction
 * @return int
*/
int	find_object_interaction(t_app *app, int start_id, t_bool direction)
{
	int		index;

	if (start_id < 0 && start_id >= MAX_INTERACTIONS)
		return (-1);
	index = start_id;
	if (direction == 1)
	{
		while (index < MAX_INTERACTIONS)
		{
			if (app->interactions[index].activation_object
				== app->current_object)
				return (index);
			index++;
		}
		return (-1);
	}
	while (index >= 0 && index < MAX_INTERACTIONS)
	{
		if (app->interactions[index].activation_object == app->current_object)
			return (index);
		index--;
	}
	return (-1);
}

/**
 * @brief Renders colored outlines for the interaction's target sector.
 * 
 * @param app
*/
void	render_target_sector_lines(t_app *app)
{
	t_wall_list	*tmp;

	tmp = app->current_interaction->target_sector->wall_list;
	while (tmp->next)
	{
		draw_list_lines(app, tmp, tmp->next, TEXT);
		if (tmp->next == app->current_interaction->target_sector->wall_list)
			break ;
		tmp = tmp->next;
	}
}
