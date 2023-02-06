/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_raycast_slopes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:06:55 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/31 15:10:33 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Calculates height offset for current rayhit based on sector ceiling
 * slope
 * 
 * @param hit 
 * @return double 
 */
double	apply_ceiling_slope(t_rayhit *hit)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	if (!hit->sector->ceil_slope_magnitude)
		return (0.0);
	slope_vector = ft_vector2_sub(hit->sector->ceil_slope_end,
			hit->sector->ceil_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(hit->position,
				hit->sector->ceil_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
				hit->position, hit->sector->ceil_slope_start));
	hit->ceil_horizon_angle = cos(ft_vector_angle(hit->ray,
				slope_vector)) / hit->distortion;
	hit->ceil_horizon = hit->sector->ceil_slope_magnitude \
				* hit->ceil_horizon_angle;
	hit->ceil_slope_height = perpendicular_distance \
				* hit->sector->ceil_slope_magnitude;
	return (perpendicular_distance * hit->sector->ceil_slope_magnitude);
}

/**
 * @brief Calculates height offset for current rayhit based on sector floor
 * slope
 * 
 * @param hit 
 * @return double 
 */
double	apply_floor_slope(t_rayhit *hit)
{
	double		perpendicular_distance;
	double		pos_angle;
	t_vector2	slope_vector;

	if (!hit->sector->floor_slope_magnitude)
		return (0.0);
	slope_vector = ft_vector2_sub(hit->sector->floor_slope_end,
			hit->sector->floor_slope_start);
	pos_angle = ft_vector_angle(ft_vector2_sub(hit->position,
				hit->sector->floor_slope_start), slope_vector);
	perpendicular_distance = cos(pos_angle) * ft_vector_length(ft_vector2_sub(
				hit->position, hit->sector->floor_slope_start));
	hit->floor_horizon_angle = cos(ft_vector_angle(hit->ray,
				slope_vector)) / hit->distortion;
	hit->floor_horizon = hit->sector->floor_slope_magnitude \
			* hit->floor_horizon_angle;
	hit->floor_slope_height = perpendicular_distance \
			* hit->sector->floor_slope_magnitude;
	return (perpendicular_distance * hit->sector->floor_slope_magnitude);
}
