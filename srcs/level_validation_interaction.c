/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_interaction.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:52:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/12 17:55:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	level_validation_interactions(t_app *app)
{
	int	i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].event_id == EVENT_NONE)
			continue ;
		if (app->interactions[i].target_sector < -1
			|| app->interactions[i].target_sector >= app->sector_count)
			exit_error(MSG_ERROR_VALIDATION_INTERACTION);
	}
}