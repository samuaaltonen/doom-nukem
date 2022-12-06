/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_trigger.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:06:52 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/06 16:40:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns animation struct for light change.
 * 
 * @param sector 
 * @param variable 
 * @return t_animation 
 */
static t_animation	get_light_animation(t_sector *sector, double variable)
{
	return ((t_animation){0.0, ANIMATION_DURATION_LIGHT,
		(variable - sector->light) / ANIMATION_DURATION_LIGHT,
		&sector->light, variable});
}

/**
 * @brief Returns animation struct for height change.
 * 
 * @param original 
 * @param variable 
 * @param target 
 * @return t_animation 
 */
static t_animation	get_height_animation(double original, double variable,
	double *target)
{
	t_animation	animation;

	animation.target = target;
	animation.progress = 0.0;
	animation.duration = ANIMATION_DURATION_HEIGHT
		* fabs(variable - original);
	animation.final_value = *target + (variable - original);
	if (variable - original < 0.0)
		animation.increment = -1.0 / ANIMATION_DURATION_HEIGHT;
	else
		animation.increment = 1.0 / ANIMATION_DURATION_HEIGHT;
	return (animation);
}

/**
 * @brief Handles animation creations for interactions that has a sector as
 * target.
 * 
 * @param app 
 * @param interaction 
 * @param variable 
 */
static void	interaction_trigger_sector(t_app *app, t_interaction *interaction,
	double variable)
{
	t_sector	*sector;

	sector = &app->sectors[interaction->target_sector];
	if (interaction->event_id == EVENT_CHANGE_LIGHT
		&& animation_create(app, get_light_animation(sector, variable)))
		interaction->variable = sector->light;
	if (interaction->event_id == EVENT_CHANGE_FLOOR_AND_CEIL_HEIGHT
		&& animation_create(app, get_height_animation(sector->floor_height,
				variable, &sector->floor_height))
		&& animation_create(app, get_height_animation(sector->floor_height,
				variable, &sector->ceil_height)))
		interaction->variable = sector->floor_height;
	if (interaction->event_id == EVENT_CHANGE_FLOOR_HEIGHT
		&& animation_create(app, get_height_animation(sector->floor_height,
				variable, &sector->floor_height)))
		interaction->variable = sector->floor_height;
	if (interaction->event_id == EVENT_CHANGE_CEIL_HEIGHT
		&& animation_create(app, get_height_animation(sector->ceil_height,
				variable, &sector->ceil_height)))
		interaction->variable = sector->ceil_height;
}

/**
 * @brief Triggers interaction.
 * 
 * @param app 
 * @param interaction_index 
 */
void	interaction_trigger(t_app *app, int interaction_index)
{
	static const char	*sound_paths[] = {SOUND_LASER_PATH, SOUND_SHOT_PATH,
		SOUND_BUMP_PATH};
	t_interaction		*interaction;
	double				variable;

	interaction = &app->interactions[interaction_index];
	variable = interaction->variable;
	if (interaction->event_id == EVENT_DISPLAY_TEXT && !app->textmodal.duration)
	{
		app->textmodal.text = (int)variable;
		if (app->textmodal.text < 0 || app->textmodal.text >= MAX_TEXT_LINES
			|| app->text_lengths[app->textmodal.text] == 0)
			return ;
		app->textmodal.duration = (double)app->text_lengths[app->textmodal.text]
			* ANIMATION_DURATION_TEXT + ANIMATION_DURATION_TEXT_END;
	}
	if (interaction->event_id == EVENT_TRIGGER_SOUND
		&& (int)variable >= 0 && (int)variable < 3)
		play_sound(app, (char *)sound_paths[(int)variable]);
	/* if (interaction->event_id == EVENT_END_LEVEL)
		app->status = STATUS_END_LEVEL; */
	if (interaction->target_sector == -1)
		return ;
	interaction_trigger_sector(app, interaction, variable);
}
