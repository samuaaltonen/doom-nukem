/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:07:09 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 16:44:51 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if given pointer already has progressing animation that
 * modifies its value.
 * 
 * @param app 
 * @param target 
 * @return t_bool 
 */
static t_bool	has_animation(t_app *app, double *target)
{
	int	i;

	i = 0;
	while (i < app->animation_count)
	{
		if (app->animations[i].target == target)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * @brief Adds animation to animation array.
 * 
 * @param app 
 * @param animation 
 * @return t_bool 
 */
t_bool	animation_create(t_app *app, t_animation animation)
{
	if (app->animation_count >= MAX_CONCURRENT_ANIMATIONS - 1
		|| has_animation(app, animation.target))
		return (FALSE);
	app->animations[app->animation_count] = animation;
	app->animation_count++;
	return (TRUE);
}
