/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:47:35 by saaltone          #+#    #+#             */
/*   Updated: 2023/02/07 18:01:22 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns relative distance to a sector wall. Gets the closest point on
 * the wall and then adds normalized unit vector that is perpendicular to the
 * wall and calculated distance to that point. Used for comparing relative
 * distances to walls from different sectors.
 * 
 * @param coord 
 * @param wall_line 
 * @return double 
 */
double	get_relative_wall_distance(t_vector2 coord, t_line wall_line)
{
	return (ft_vector_length(ft_vector2_sub(coord,
				ft_vector2_add(ft_closest_point(coord, wall_line),
					ft_vector2_normalize(ft_vector_perpendicular(
							ft_vector2_sub(wall_line.b, wall_line.a)))))));
}

/**
 * @brief Returns wall vector from sector by wall id.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_vector2 
 */
t_vector2	get_wall_vector(t_app *app, int sector_id, int wall_id)
{
	if (app->sectors[sector_id].corner_count == wall_id + 1)
		return (ft_vector2_sub(app->sectors[sector_id].corners[0],
				app->sectors[sector_id].corners[wall_id]));
	return (ft_vector2_sub(app->sectors[sector_id].corners[wall_id + 1],
			app->sectors[sector_id].corners[wall_id]));
}

/**
 * @brief Returns line from sector by wall id.
 * 
 * @param app 
 * @param sector_id 
 * @param wall_id 
 * @return t_line 
 */
t_line	get_wall_line(t_app *app, int sector_id, int wall_id)
{
	if (app->sectors[sector_id].corner_count == wall_id + 1)
		return ((t_line){
			app->sectors[sector_id].corners[wall_id],
			app->sectors[sector_id].corners[0],
		});
	return ((t_line){
		app->sectors[sector_id].corners[wall_id],
		app->sectors[sector_id].corners[wall_id + 1],
	});
}
