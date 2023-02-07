/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:48:10 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/07 16:47:00 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Maps the point given from the source rectangle to the appropiate 
 * coordinates on the destination rectangle.
 * 
 * @param src 
 * @param dst 
 * @param point 
 */
void	map_coordinates(t_rect *src, t_rect *dst, t_point *point)
{
	point->x = point->x * ((float)dst->w / (float)src->w) + dst->x;
	point->y = point->y * ((float)dst->h / (float)src->h) + dst->y;
}

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
