/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_validation_object.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:26:41 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/13 16:01:37 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if level object data is valid.
 * 
 * @param app 
 */
void	level_validation_objects(t_app *app)
{
	int	i;

	i = -1;
	while (++i < MAX_OBJECTS)
	{
		if (app->objects[i].sector < 0
			|| app->objects[i].sector >= app->sector_count
			|| app->objects[i].type < 0
			|| app->objects[i].type > MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS
			+ MAX_ENEMY_TYPES)
			exit_error(MSG_ERROR_VALIDATION_OBJECT);
	}
}
