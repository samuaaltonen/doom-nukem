/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:21:17 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 22:30:20 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static int	enemy_check_members(t_app *app, t_enemy_state *enemy, t_point info,
		t_move new)
{
	int	i;
	int	member_id;
	int	portal_id;

	i = -1;
	member_id = app->sectors[info.y].member_sectors[info.x];
	while (++i < app->sectors[member_id].corner_count)
	{
		if (ft_line_side(get_wall_line(app, member_id, i), new.pos) != 0)
			break ;
	}
	if (i != app->sectors[member_id].corner_count)
		return (-1);
	portal_id = enemy_move_check(app, new, member_id, enemy);
	if (portal_id < 0 || (new.elevation + MAX_STEP
			< app->sectors[portal_id].floor_height
			|| app->sectors[portal_id].ceil_height < new.elevation
			+ app->player.height))
		return (-1);
	else
	{
		app->objects[enemy->id].sector = portal_id;
		return (portal_id);
	}
	return (-1);
}

static int	enemy_check_main(t_app *app, t_enemy_state *enemy, t_point info,
		t_move new)
{
	t_line	wall_line;
	int		portal_id;

	wall_line = get_wall_line(app, info.y, info.x);
	if (!ft_line_side(wall_line, new.pos))
		return (info.y);
	if (!ft_line_intersection_segment((t_line){app->objects[enemy->id].position,
			new.pos}, wall_line, NULL))
		return (info.y);
	portal_id = app->sectors[info.y].wall_types[info.x];
	if (portal_id < 0 || app->sectors[info.y].wall_textures[info.x]
		== PARTIALLY_TRANSPARENT_TEXTURE_ID)
		return (-1);
	if (!portal_can_enter(app, ft_vec2_to_vec3(new.pos, new.elevation), 0.5f,
			wall_line, app->objects[enemy->id].sector,
			app->sectors[app->objects[enemy->id].sector].wall_types[info.x]))
		return (-1);
	portal_id = enemy_move_check(app, new, portal_id, enemy);
	if (portal_id < 0)
		return (-1);
	else
	{
		app->objects[enemy->id].sector = portal_id;
		return (portal_id);
	}
}

/**
 * @brief Checks if enemy new position is on the otherside of any wall,
 * 	recurses into the new sector if it's a portal,
 * 	returns -1 if the enemy can't be in the new position
 * 
 * @param app 
 * @param new 
 * @param sector_id 
 * @return int 
 */
int	enemy_move_check(t_app *app, t_move new, int sector_id,
		t_enemy_state *enemy)
{
	int		i;
	int		counter;

	counter = 0;
	while (app->sectors[sector_id].member_sectors[counter] >= 0)
	{
		enemy_check_members(app, enemy, (t_point){counter, sector_id}, new);
		counter++;
	}
	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
		enemy_check_main(app, enemy, (t_point){i, sector_id}, new);
	return (sector_id);
}
