/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/08 14:24:55 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Clamps given number to the range from min to max.
 * 
 * @param number 
 * @param min 
 * @param max 
 */
void	clamp_int(int *number, int min, int max)
{
	if (*number < min)
		*number = min;
	if (*number > max)
		*number = max;
}

/**
 * @brief Checks if object is inside a visible sector.
 * 
 * @param app 
 * @param id 
 * @return t_bool 
 */
t_bool	obj_seen(t_app *app, int id)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		if (app->sectors[app->objects[id].sector].is_visible[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}
