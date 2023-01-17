/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_progress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:52:16 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 13:57:11 by saaltone         ###   ########.fr       */
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
	if (app->animations[index].trigger_after >= 0)
		interaction_trigger(app, app->animations[index].trigger_after);
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
	if (app->textmodal.duration > 0.0)
	{
		app->textmodal.progress += app->conf->delta_time;
		if (app->textmodal.progress >= app->textmodal.duration)
		{
			app->textmodal.progress = 0.0;
			app->textmodal.duration = 0.0;
			if (app->textmodal.trigger_after >= 0)
				interaction_trigger(app, app->textmodal.trigger_after);
		}
	}
}
