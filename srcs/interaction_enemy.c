/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_enemy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:14:26 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/06 19:36:48 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks and triggers enemy related interactions.
 * 
 * @param app 
 * @param enemy 
 */
void	enemy_interaction_check(t_app *app, t_enemy_state *enemy)
{
	int	i;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].event_id == EVENT_NONE)
			continue ;
		if (app->interactions[i].activation_object == enemy->id
			&& check_key_requirement(app, &app->interactions[i]))
			interaction_trigger(app, i);
	}
}
