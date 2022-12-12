/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_elevation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:29:29 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/12 15:42:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Get the sector floor height at specific coordinate.
 * 
 * @param app 
 * @param sector_id 
 * @param pos 
 * @return double 
 */
double	get_sector_floor_height(t_app *app, int sector_id, t_vector2 pos)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	if (!app->sectors[sector_id].floor_slope_magnitude)
		return (app->sectors[sector_id].floor_height);
	slope_vector = ft_vector2_sub(app->sectors[sector_id].floor_slope_end,
			app->sectors[sector_id].floor_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(pos,
				app->sectors[sector_id].floor_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
				pos, app->sectors[sector_id].floor_slope_start));
	return (app->sectors[sector_id].floor_height + perpendicular_distance
		* app->sectors[sector_id].floor_slope_magnitude);
}

/**
 * @brief Get the sector ceiling height at specific coordinate.
 * 
 * @param app 
 * @param sector_id 
 * @param pos 
 * @return double 
 */
double	get_sector_ceil_height(t_app *app, int sector_id, t_vector2 pos)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	if (!app->sectors[sector_id].ceil_slope_magnitude)
		return (app->sectors[sector_id].ceil_height);
	slope_vector = ft_vector2_sub(app->sectors[sector_id].ceil_slope_end,
			app->sectors[sector_id].ceil_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(pos,
				app->sectors[sector_id].ceil_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
				pos, app->sectors[sector_id].ceil_slope_start));
	return (app->sectors[sector_id].ceil_height + perpendicular_distance
		* app->sectors[sector_id].ceil_slope_magnitude);
}
