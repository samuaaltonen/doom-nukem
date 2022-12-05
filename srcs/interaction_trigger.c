/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_trigger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:06:52 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 16:33:02 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_animation	get_height_animation(t_sector *sector, t_interaction *interaction, double *target)
{
	t_animation	animation;

	animation.target = target;
	animation.progress = 0.0;
	animation.duration = ANIMATION_DURATION_HEIGHT * fabs(interaction->variable - sector->floor_height);
	if (interaction->variable - sector->floor_height < 0.0)
		animation.increment = -1.0 / ANIMATION_DURATION_HEIGHT;
	else
		animation.increment = 1.0 / ANIMATION_DURATION_HEIGHT;
	return (animation);
}

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
	double			previous_value;

	interaction = &app->interactions[interaction_index];
	if (interaction->target_sector == -1)
		return ;
	target_sector = &app->sectors[interaction->target_sector];
	if (interaction->event_id == EVENT_CHANGE_LIGHT
		&& animation_create(app, (t_animation){0.0, ANIMATION_DURATION_LIGHT,
			(interaction->variable - target_sector->light)
				/ ANIMATION_DURATION_LIGHT, &target_sector->light}))
		previous_value = target_sector->light;
	if ((interaction->event_id == EVENT_CHANGE_FLOOR_HEIGHT || interaction->event_id == EVENT_CHANGE_FLOOR_AND_CEIL_HEIGHT)
		&& animation_create(app, get_height_animation(target_sector, interaction, &target_sector->floor_height)))
		previous_value = target_sector->floor_height;
	if ((interaction->event_id == EVENT_CHANGE_CEIL_HEIGHT || interaction->event_id == EVENT_CHANGE_FLOOR_AND_CEIL_HEIGHT)
		&& animation_create(app, get_height_animation(target_sector, interaction, &target_sector->ceil_height)))
		previous_value = target_sector->floor_height;
	interaction->variable = previous_value;
}
