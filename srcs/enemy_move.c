/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:21:17 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/03 13:34:24 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
int	enemy_move_check(t_app *app, t_move new, int sector_id, t_enemy_state *enemy)
{
	t_line	wall_line;
	int		i;
	int		member_id;
	int		portal_id;
	int		counter;

//member sector walls
	counter = 0;
	while(app->sectors[sector_id].member_sectors[counter] >= 0)
	{
		i = -1;
		member_id = app->sectors[sector_id].member_sectors[counter];
		while (++i < app->sectors[member_id].corner_count)
		{
			if(ft_line_side(get_wall_line(app, member_id ,i), new.pos) != 0)
				break;
		}
		if(i == app->sectors[member_id].corner_count)
		{
			portal_id = enemy_move_check(app, new, member_id, enemy);
			if(portal_id < 0 || (new.elevation + MAX_STEP < app->sectors[portal_id].floor_height ||
				app->sectors[portal_id].ceil_height < new.elevation + app->player.height))
				return (-1);
			else
			{
				app->objects[enemy->id].sector = portal_id;
				return(portal_id);
			}
		}
		counter++;
	}

	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		wall_line = get_wall_line(app, sector_id, i);
		if (!ft_line_side(wall_line, new.pos))
			continue ;
		if (!ft_line_intersection_segment((t_line){app->objects[enemy->id].position, new.pos}, wall_line, NULL))
			continue ;
		portal_id = app->sectors[sector_id].wall_types[i];
		if (portal_id < 0
			|| (new.elevation + MAX_STEP < app->sectors[portal_id].floor_height
				||	app->sectors[portal_id].ceil_height < new.elevation + app->player.height))
			return (-1);
		else
		{
			if (app->sectors[sector_id].wall_textures[i] == PARTIALLY_TRANSPARENT_TEXTURE_ID)
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
	}
	return (sector_id);
}