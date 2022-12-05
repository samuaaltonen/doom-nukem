/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_progress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:52:16 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 16:48:27 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Destroys animation from animations array.
 * 
 * @param app 
 * @param index 
 */
static void	animation_destroy(t_app *app, int index)
{
	*app->animations[index].target = app->animations[index].final_value;
	if (index < app->animation_count - 1)
		app->animations[index] = app->animations[app->animation_count - 1];
	app->animation_count--;
}

/**
 * @brief Progresses game animations.
 * 
 * @param app 
 */
void	progress_animations(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->animation_count)
	{
		*app->animations[i].target += app->animations[i].increment
			* app->conf->delta_time;
		app->animations[i].progress += app->conf->delta_time;
		if (app->animations[i].progress >= app->animations[i].duration)
			animation_destroy(app, i);
		i++;
	}
}
