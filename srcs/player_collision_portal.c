/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision_portal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:55:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 16:33:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns TRUE if it is possible to enter portal based on height
 * differences.
 * 
 * @param app 
 * @param pos 
 * @param wall 
 * @param sectors (x for source sector, y for target sector, z for height)
 * @return t_bool 
 */
t_bool	portal_can_enter(t_app *app, t_vector3 pos, t_line wall,
	t_vector3 sectors)
{
	t_vector2	check_pos;
	double		source_floor;
	double		source_ceil;
	double		target_floor;
	double		target_ceil;

	check_pos = ft_closest_point((t_vector2){pos.x, pos.y}, wall);
	source_floor = sector_floor_height(app, sectors.x, check_pos);
	source_ceil = sector_ceil_height(app, sectors.x, check_pos);
	target_floor = sector_floor_height(app, sectors.y, check_pos);
	target_ceil = sector_ceil_height(app, sectors.y, check_pos);
	if (pos.z + MAX_STEP < target_floor
		&& source_floor + MAX_STEP < target_floor)
		return (FALSE);
	if (target_ceil < pos.z + sectors.z
		+ COLLISION_CEIL && source_ceil - MAX_STEP > target_ceil)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Checks if heightless projectile can enter the portal.
 * 
 * @param app 
 * @param pos 
 * @param wall 
 * @param sectors (x for source sector and y for target sector)
 * @return t_bool 
 */
t_bool	projectile_can_enter(t_app *app, t_vector3 pos, t_line wall,
	t_point sectors)
{
	t_vector2	check_pos;
	double		source_floor;
	double		source_ceil;
	double		target_floor;
	double		target_ceil;

	if (sectors.y == -1)
		return (FALSE);
	check_pos = ft_closest_point((t_vector2){pos.x, pos.y}, wall);
	source_floor = sector_floor_height(app, sectors.x, check_pos);
	source_ceil = sector_ceil_height(app, sectors.x, check_pos);
	target_floor = sector_floor_height(app, sectors.y, check_pos);
	target_ceil = sector_ceil_height(app, sectors.y, check_pos);
	if (pos.z < target_floor)
		return (FALSE);
	if (target_ceil < pos.z)
		return (FALSE);
	if (pos.z < source_floor)
		return (FALSE);
	if (source_ceil < pos.z)
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
