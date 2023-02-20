/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_interaction.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:52:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/20 14:05:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if interaction data is valid.
 * 
 * @param app 
 */
void	level_validation_interactions(t_app *app)
{
	int	i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].event_id == EVENT_NONE)
			continue ;
		if (app->interactions[i].activation_sector < -1
			|| app->interactions[i].activation_sector >= app->sector_count
			|| app->interactions[i].target_sector < -1
			|| app->interactions[i].target_sector >= app->sector_count
			|| app->interactions[i].interaction_link < -1
			|| app->interactions[i].interaction_link >= MAX_INTERACTIONS
			|| app->interactions[i].activation_wall < -1
			|| app->interactions[i].activation_object < -1)
			exit_error(MSG_ERROR_VALIDATION_INTERACTION);
		if (app->interactions[i].activation_wall != -1
			&& app->sectors[app->interactions[i].activation_sector].corner_count
			<= app->interactions[i].activation_wall)
			exit_error(MSG_ERROR_VALIDATION_INTERACTION);
		if (app->interactions[i].activation_object >= 0
			&& app->interactions[i].activation_object >= MAX_OBJECTS)
			exit_error(MSG_ERROR_VALIDATION_INTERACTION);
	}
}
