/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_avoidance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:30:02 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 14:06:37 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	init_colliders(t_app *app, t_enemy_state *enemy,
		t_vector2 *colliders, int *collider)
{
	*collider = -1;
	colliders[0] = (t_vector2){app->objects[enemy->id].position.x
		- ENEMY_COLLISION + 0.01f, app->objects[enemy->id].position.y
		- ENEMY_COLLISION};
	colliders[1] = (t_vector2){app->objects[enemy->id].position.x
		+ ENEMY_COLLISION, app->objects[enemy->id].position.y
		- ENEMY_COLLISION};
	colliders[2] = (t_vector2){app->objects[enemy->id].position.x
		- ENEMY_COLLISION + 0.01f, app->objects[enemy->id].position.y
		+ ENEMY_COLLISION};
	colliders[3] = (t_vector2){app->objects[enemy->id].position.x
		+ ENEMY_COLLISION, app->objects[enemy->id].position.y
		+ ENEMY_COLLISION};
}

static void	member_wall_hits(t_app *app, t_enemy_state *enemy, t_bool *hits,
		t_vector2 *colliders)
{
	int				collider;
	int				i;
	t_sector		*current;
	t_gameobject	*data;

	data = &(app->objects[enemy->id]);
	current = &(app->sectors[data->sector]);
	if (current->member_sectors[0] == -1)
		return ;
	collider = -1;
	while (++collider < 4)
	{
		i = -1;
		while (current->member_sectors[++i] != -1)
		{
			if (!inside_sector(app, current->member_sectors[i],
					colliders[collider])
				|| portal_can_enter(app, ft_vec2_to_vec3(data->position,
						data->elevation), (t_vector3){data->sector,
					current->member_sectors[i], 0.5f}))
				continue ;
			hits[collider] = TRUE;
			hits[4] = TRUE;
		}
	}
}

static void	parent_wall_hits(t_app *app, t_enemy_state *enemy, t_bool *hits,
		t_vector2 *colliders)
{
	int	collider;
	int	sector_id;

	sector_id = app->objects[enemy->id].sector;
	if (app->sectors[sector_id].parent_sector == -1)
		return ;
	collider = -1;
	while (++collider < 4)
	{
		if (!inside_sector(app, sector_id, colliders[collider])
			&& !portal_can_enter(app, ft_vec2_to_vec3(
					app->objects[enemy->id].position,
					app->objects[enemy->id].elevation),
				(t_vector3){sector_id,
				app->sectors[sector_id].parent_sector, 0.5f}))
		{
			hits[collider] = TRUE;
			hits[4] = TRUE;
		}
	}
}

static void	collect_hits(t_app *app, t_enemy_state *enemy, t_bool *hits,
		t_vector2 *colliders)
{
	int		collider;
	int		i;
	t_line	wall_line;

	parent_wall_hits(app, enemy, hits, colliders);
	collider = -1;
	while (++collider < 4)
	{
		i = -1;
		while (++i < app->sectors[app->objects[enemy->id].sector].corner_count)
		{
			wall_line = get_wall_line(app, app->objects[enemy->id].sector, i);
			if (!ft_line_side(wall_line, colliders[collider]))
				continue ;
			if (ft_point_on_segment(wall_line,
					ft_closest_point(colliders[collider], wall_line))
				&& app->sectors[app->objects[enemy->id] \
						.sector].wall_types[i] == -1)
			{
				hits[collider] = TRUE;
				hits[4] = TRUE;
			}
		}
	}
	member_wall_hits(app, enemy, hits, colliders);
}

/**
 * @brief Makes 4 colliders around the enemy, collects which of the colliders
 * 	hit walls, adds them and creates a direction away from the collided points
 * 
 * @param app 
 * @param enemy 
 */
void	avoid_walls(t_app *app, t_enemy_state *enemy)
{
	t_vector2	colliders[4];
	int			collider;
	t_bool		hit[5];
	t_vector2	new;

	init_colliders(app, enemy, (t_vector2 *)colliders, &collider);
	ft_bzero(&hit, sizeof(hit));
	collect_hits(app, enemy, (t_bool *)&hit, (t_vector2 *)colliders);
	if (hit[4])
	{
		new = app->objects[enemy->id].position;
		while (++collider < 4)
		{
			if (!hit[collider])
				continue ;
			new = ft_vector2_add(new, ft_vector2_sub(colliders[collider],
						app->objects[enemy->id].position));
		}
		enemy->dir = ft_vector2_normalize(ft_vector2_sub(
					app->objects[enemy->id].position, new));
		app->objects[enemy->id].rot = ft_vector_angle_left(
				(t_vector2){0.f, -1.f}, enemy->dir);
	}
}
