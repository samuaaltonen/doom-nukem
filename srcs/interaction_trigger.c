/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_trigger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:06:52 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 13:18:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Triggers interaction.
 * 
 * @param app 
 * @param interaction_index 
 */
t_bool	interaction_trigger(t_app *app, int interaction_index)
{
	t_interaction	interaction;

	interaction = app->interactions[interaction_index];
	if (interaction.event_id == EVENT_CHANGE_LIGHT)
		return (animation_create(app, (t_animation){0.0, DURATION_LIGHT,
			(void *)&app->sectors[interaction.target_sector], TYPE_DOUBLE}));
}
