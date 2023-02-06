/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_pickup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:04:27 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/06 18:04:59 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks and triggers interactions from pickable objects.
 * 
 * @param app 
 * @param obj 
 */
void	interaction_by_pickup(t_app *app, t_gameobject *obj)
{
	int				i;
	t_gameobject	*tmp;

	i = -1;
	while (++i < MAX_INTERACTIONS)
	{
		if (app->interactions[i].activation_object != 1)
		{
			tmp = &(app->objects[app->interactions[i].activation_object]);
			if (tmp != obj)
				continue ;
			interaction_trigger(app, i);
		}
	}
}
