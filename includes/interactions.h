/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:47:58 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/12 14:49:07 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIONS_H
# define INTERACTIONS_H

/**
 * Event type enumeration.
 */
enum e_event_id {
	EVENT_NONE,
	EVENT_CHANGE_FLOOR_HEIGHT,
	EVENT_CHANGE_CEIL_HEIGHT,
	EVENT_CHANGE_FLOOR_AND_CEIL_HEIGHT,
	EVENT_CHANGE_LIGHT,
	EVENT_DISPLAY_TEXT,
	EVENT_TRIGGER_SOUND,
	EVENT_END_LEVEL
};

/**
 * Struct that contains information about event that gets triggered based on
 * activation rules.
 */
typedef struct s_interaction
{
	int				event_id;
	double			variable;
	double			editable;
	int				activation_sector;
	int				activation_wall;
	int				activation_object;
	int				target_sector;
}	t_interaction;

/**
 * Animation struct that contains information about animation duration and its
 * progress. Also contains pointer to a variable that is modified every time
 * animation progresses.
 */
typedef struct s_animation
{
	double	progress;
	double	duration;
	double	increment;
	double	*target;
	double	final_value;
}	t_animation;

/**
 * Animation struct for textmodals.
 */
typedef struct s_textmodal
{
	double	progress;
	double	duration;
	int		text;
}	t_textmodal;

#endif
