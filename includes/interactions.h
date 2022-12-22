/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:47:58 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/22 22:45:58 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERACTIONS_H
# define INTERACTIONS_H

# define DECOR_SIZE 1.0
# define INTERACTION_ACTION_DISTANCE 1.5
# define MAX_CONCURRENT_ANIMATIONS 16
# define ANIMATION_DURATION_LIGHT 0.5 // seconds per light level
# define ANIMATION_DURATION_HEIGHT 0.25 // seconds per meter
# define ANIMATION_DURATION_TEXT 0.015625 // seconds per char
# define ANIMATION_DURATION_TEXT_END 3.5 // seconds after full text displayed
# define MAX_TEXT_LINES 16
# define MAX_TEXT_LINE_LENGTH 1024

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
