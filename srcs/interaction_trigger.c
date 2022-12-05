/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_trigger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:06:52 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 14:33:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Triggers interaction.
 * 
 * @param app 
 * @param interaction_index 
 */
void	interaction_trigger(t_app *app, int interaction_index)
{
	t_interaction	*interaction;
	t_sector		*target_sector;

	interaction = &app->interactions[interaction_index];
	if (interaction->target_sector == -1)
		return ;
	target_sector = &app->sectors[interaction->target_sector];
	if (interaction->event_id == EVENT_CHANGE_LIGHT
		&& animation_create(app, (t_animation){0.0, DURATION_LIGHT,
			(interaction->variable - target_sector->light) / DURATION_LIGHT,
			&target_sector->light}))
		interaction->variable = target_sector->light;
}
