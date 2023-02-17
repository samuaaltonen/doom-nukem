/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_avoidance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:30:02 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/17 19:37:16 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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

static t_bool	main_wall_hit(t_app *app, t_enemy_state *enemy,
		t_vector2 *collider, int wall_id)
{
	t_line	wall_line;

	wall_line = get_wall_line(app, app->objects[enemy->id].sector, wall_id);
	if (!ft_line_side(wall_line, *collider))
		return (FALSE);
	if (ft_point_on_segment(wall_line,
			ft_closest_point(*collider, wall_line))
		&& ((app->sectors[app->objects[enemy->id].sector].wall_types[wall_id]
				== -1 || app->sectors[app->objects[enemy->id].sector] \
				.wall_textures[wall_id]
				<= PARTIALLY_TRANSPARENT_TEXTURE_ID)
			|| !portal_can_enter(app,
				(t_vector3){collider->x, collider->y,
				app->objects[enemy->id].elevation},
			(t_vector3){app->objects[enemy->id].sector,
			app->sectors[app->objects[enemy->id].sector] \
			.wall_types[wall_id],
			app->objects[enemy->id].elevation})))
		return (TRUE);
	return (FALSE);
}

void	collect_hits(t_app *app, t_enemy_state *enemy, t_bool *hits,
		t_vector2 *colliders)
{
	int		collider;
	int		i;

	parent_wall_hits(app, enemy, hits, colliders);
	collider = -1;
	while (++collider < 4)
	{
		i = -1;
		while (++i < app->sectors[app->objects[enemy->id].sector].corner_count)
		{
			if (main_wall_hit(app, enemy, &(colliders[collider]), i))
			{
				hits[collider] = TRUE;
				hits[4] = TRUE;
			}
		}
	}
	member_wall_hits(app, enemy, hits, colliders);
}
