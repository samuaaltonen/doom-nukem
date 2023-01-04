/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:01:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/04 14:55:39 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"


static void	projectile_flight(t_app *app, t_move *new, t_projectile *projectile, t_bool init)
{
	t_line		wall_line;
	int			i;
	int			member_id;
	int			counter;
	static int	recursion_count;

	(void)counter;
	(void)member_id;
	if(init)
		recursion_count = 0;
	recursion_count++;

	if(recursion_count < MAX_VISIBLE_SECTORS)
		return ;

//member sector walls
/* 	counter = 0;
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
			projectile->sector = projectile_flight(app, new, member_id, enemy);
			if(projectile->sector < 0 || (new.elevation + MAX_STEP < app->sectors[projectile->sector].floor_height ||
				app->sectors[projectile->sector].ceil_height < new.elevation + app->player.height))
				return (-1);
			else
			{
				app->objects[enemy->id].sector = projectile->sector;
				return(projectile->sector);
			}
		}
		counter++;
	} */

	i = -1;
	while (++i < app->sectors[projectile->sector].corner_count)
	{
		wall_line = get_wall_line(app, projectile->sector, i);
		if (!ft_line_side(wall_line, new->pos))
			continue ;
		if (!ft_line_intersection_segment((t_line){projectile->start, new->pos}, wall_line, &(projectile->end)))
			continue ;
		projectile->sector = app->sectors[projectile->sector].wall_types[i];
		if (projectile->sector < 0 || app->sectors[projectile->sector].wall_textures[i] == PARTIALLY_TRANSPARENT_TEXTURE_ID
			|| (new->elevation < app->sectors[projectile->sector].floor_height
				||	app->sectors[projectile->sector].ceil_height < new->elevation))
			return ;
		projectile_flight(app, new, projectile, FALSE);
		return ;
	}
}

static void calc_end(t_app *app, t_projectile *projectile, t_vector3 target_dir)
{
	t_move new;

	new.pos = ft_vector2_add(projectile->start, ft_vector_resize((t_vector2){target_dir.x,target_dir.y}, 10.f));
	new.elevation = target_dir.z; //temp use of z directly maybe
	new.elevation *= 10.f;
	projectile_flight(app, &new, projectile, TRUE);
}

//info.x = type, info.y = sector
void	fire(t_app *app, t_vector3 target_dir, t_vector3 start_pos, t_point info)
{
	int	i;

	i = -1;
	while(++i < MAX_TEMP_OBJECTS)
	{
		if(app->projectiles[i].type == -1)
		{
			app->projectiles[i].start = (t_vector2){start_pos.x, start_pos.y};
			app->projectiles[i].start_z = start_pos.z;
			app->projectiles[i].type = info.x;
			app->projectiles[i].sector = info.y;
			calc_end(app, &(app->projectiles[i]), target_dir);
			app->projectiles[i].timer = ft_vector_length(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start)) / 5.f;
			app->projectiles[i].end = ft_vector2_normalize(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start));
			return;
		}
	}
}

void	update_projectiles(t_app *app)
{
	int	i;

	i = -1;
	while (++i < MAX_TEMP_OBJECTS)
	{
		if(app->projectiles[i].type == -1)
			continue;
		app->projectiles[i].start = ft_vector2_add(app->projectiles[i].start,ft_vec2_mult(app->projectiles[i].end, app->conf->delta_time * 5.f));
		if(app->projectiles[i].timer > 0)
			app->projectiles[i].timer -= app->conf->delta_time;
		else
			app->projectiles[i].type = -1; //event to explode
	}
}