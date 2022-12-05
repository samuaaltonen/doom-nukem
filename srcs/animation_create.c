/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:07:09 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/05 14:40:50 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Adds animation to animation array.
 * 
 * @param app 
 * @param animation 
 * @return t_bool 
 */
t_bool	animation_create(t_app *app, t_animation animation)
{
	if (app->animation_count >= MAX_CONCURRENT_ANIMATIONS - 1)
		return (FALSE);
	app->animations[app->animation_count] = animation;
	app->animation_count++;
	return (TRUE);
}
