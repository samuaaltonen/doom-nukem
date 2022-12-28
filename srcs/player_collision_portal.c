/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_portal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:55:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/28 14:39:28 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns TRUE if it is possible to enter portal based on height
 * differences.
 * 
 * @param app 
 * @param wall 
 * @param source_sector 
 * @param target_sector 
 * @return t_bool 
 */
t_bool	portal_can_enter(t_app *app, t_line wall, int source_sector,
	int target_sector)
{
	t_vector2	check_pos;
	double		source_floor;
	double		source_ceil;
	double		target_floor;
	double		target_ceil;

	check_pos = ft_closest_point(app->player.move_pos, wall);
	source_floor = sector_floor_height(app, source_sector, check_pos);
	source_ceil = sector_ceil_height(app, source_sector, check_pos);
	target_floor = sector_floor_height(app, target_sector, check_pos);
	target_ceil = sector_ceil_height(app, target_sector, check_pos);
	if (app->player.elevation + MAX_STEP < target_floor
		&& source_floor + MAX_STEP < target_floor)
		return (FALSE);
	if (target_ceil < app->player.elevation + app->player.height
		+ COLLISION_CEIL && source_ceil - MAX_STEP > target_ceil)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Changes players sector.
 * 
 * @param app 
 * @param sector_id 
 */
void	portal_enter(t_app *app, int sector_id)
{
	double	target_floor;

	target_floor = sector_floor_height(app, sector_id,
			app->player.move_pos);
	app->player.sector = sector_id;
	interaction_check_portal(app, sector_id);
	if (app->player.elevation != target_floor)
		app->player.flying = TRUE;
}
