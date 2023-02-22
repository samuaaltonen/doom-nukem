/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:21:17 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/22 15:07:14 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Checks if enemy is actually inside a member sector and if so it
 * changes its sector to member sector id and applies elevation.
 * 
 * @param app 
 * @param state 
 */
void	check_enemy_sector(t_app *app, t_enemy_state *state)
{
	int	i;
	int	sector_id;

	sector_id = app->objects[state->id].sector;
	if (app->sectors[sector_id].parent_sector != -1)
		return ;
	i = -1;
	while (++i < MAX_MEMBER_SECTORS
		&& app->sectors[sector_id].member_sectors[i] >= 0)
	{
		if (inside_sector(app,
				app->sectors[sector_id].member_sectors[i],
				app->objects[state->id].position))
		{
			app->objects[state->id].sector
				= app->sectors[sector_id].member_sectors[i];
			state->target_elevation = sector_floor_height(app,
					app->sectors[sector_id].member_sectors[i],
					app->objects[state->id].position);
			return ;
		}
	}
}

/**
 * @brief Recurses to check if enemy moved into new main(parent sectors)
 * 
 * @param app 
 * @param move 
 * @param sector_id 
 * @param enemy 
 * @return int 
 */
static int	enemy_move_main(t_app *app, t_move move, int sector_id,
	t_enemy_state *enemy)
{
	int				i;
	t_vector2		hit;
	t_line			wall_line;
	int				portal_id;
	t_gameobject	*status;

	i = -1;
	while (++i < app->sectors[sector_id].corner_count)
	{
		wall_line = get_wall_line(app, sector_id, i);
		status = &(app->objects[enemy->id]);
		if (!ft_line_side(wall_line, move.pos) || !ft_line_intersection_segment(
				(t_line){status->position, move.pos}, wall_line, &hit))
			continue ;
		portal_id = app->sectors[sector_id].wall_types[i];
		if (portal_id < 0 || app->sectors[sector_id].wall_textures[i]
			<= PARTIALLY_TRANSPARENT_TEXTURE_ID || !portal_can_enter(app,
				ft_vec2_to_vec3(status->position, enemy->target_elevation),
				(t_vector3){status->sector, portal_id, 0.5f}))
			return (-1);
		enemy->target_elevation = sector_floor_height(app, portal_id, hit);
		status->position = hit;
		enemy_move_check(app, move, portal_id, enemy);
	}
	return (sector_id);
}

/**
 * @brief Checks if player moved into any member sectors
 * 	otherwise continues to check main(parent sectors)
 * 
 * @param app 
 * @param new 
 * @param sector_id 
 * @param enemy 
 * @return int 
 */
int	enemy_move_check(t_app *app, t_move new, int sector_id,
	t_enemy_state *enemy)
{
	int		member_id;
	int		counter;

	app->objects[enemy->id].sector = sector_id;
	counter = -1;
	while (app->sectors[sector_id].member_sectors[++counter] >= 0)
	{
		member_id = app->sectors[sector_id].member_sectors[counter];
		if (member_id != -1 && inside_sector(app, member_id, new.pos))
		{
			if (portal_can_enter(app, ft_vec2_to_vec3(new.pos,
						enemy->target_elevation),
					(t_vector3){app->objects[enemy->id].sector,
					member_id, 0.5f}))
			{
				app->objects[enemy->id].sector = member_id;
				return (member_id);
			}
			return (-1);
		}
	}
	return (enemy_move_main(app, new, sector_id, enemy));
}
