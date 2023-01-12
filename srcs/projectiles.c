/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:01:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/12 17:55:17 by htahvana         ###   ########.fr       */
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

	if(recursion_count > MAX_VISIBLE_SECTORS)
		return ;
	if(app->sectors[projectile->sector].parent_sector != -1)
		projectile->sector = app->sectors[projectile->sector].parent_sector;

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
		projectile->end = new->pos;
		wall_line = get_wall_line(app, projectile->sector, i);
		if (!ft_line_side(wall_line, new->pos))
			continue ;
		if (!ft_line_intersection_segment((t_line){projectile->start, new->pos}, wall_line, &(projectile->end)))
			continue ;
		if (app->sectors[projectile->sector].wall_types[i] < 0 || app->sectors[projectile->sector].wall_textures[i] == PARTIALLY_TRANSPARENT_TEXTURE_ID)
			return ;
		double dist = ft_vector_length(ft_vector2_sub(projectile->end, projectile->start));
		if(!portal_can_enter(app, ft_vec2_to_vec3(projectile->end, projectile->start_z + dist * projectile->end_z), 0.0f, wall_line, projectile->sector, app->sectors[projectile->sector].wall_types[i]))
		{
			ft_printf("portal fail\n");
			return ;
		}
		projectile->end = new->pos;
		projectile->sector = app->sectors[projectile->sector].wall_types[i];
		projectile_flight(app, new, projectile, FALSE);
		return ;
	}
}

static void calc_end(t_app *app, t_projectile *projectile, t_vector3 target_dir)
{
	t_move new;

	new.pos = ft_vector2_add(projectile->start, ft_vec2_mult((t_vector2){target_dir.x,target_dir.y}, 10.f));
	new.elevation = target_dir.z * 10.f; //temp use of z directly maybe
	projectile->end_z = target_dir.z;
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
			app->projectiles[i].timer = ft_vector_length(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start)) / app->projectile_def[app->projectiles[i].type - 11].speed;
			app->projectiles[i].end = ft_vector2_normalize(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start));
			if(app->projectiles[i].type == 15)
			{
				app->projectiles[i].timer = 0.25f;
				app->projectiles[i].end = (t_vector2){0.f,0.f};
				app->projectiles[i].end_z = 0.f;
			}
			app->projectiles_active++;
			return;
		}
	}
}

void	kill_projectile(t_app *app, t_projectile *projectile)
{
			//event to explode creates a new melee attack type explosion
			if(projectile->type == 18)
				melee(app,(t_vector3){0.f,0.f,0.f}, ft_vec2_to_vec3(ft_vector2_sub(projectile->start, ft_vec2_mult(projectile->end, 0.25f)), projectile->start_z - projectile->end_z * 0.25f),(t_point){12,projectile->sector});
			projectile->type = -1;
			app->projectiles_active--;
}

void	melee(t_app *app, t_vector3 target_dir, t_vector3 start_pos, t_point info)
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
			app->projectiles[i].timer = ft_vector_length(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start)) / app->projectile_def[app->projectiles[i].type - 11].speed;
			app->projectiles[i].end = ft_vector2_normalize(ft_vector2_sub(app->projectiles[i].end, app->projectiles[i].start));
			app->projectiles[i].timer = 0.25f;
			if(!(app->projectiles[i].type == 0))
				app->projectiles[i].start = ft_vector2_add(app->projectiles[i].start, app->projectiles[i].end);
			app->projectiles[i].end = (t_vector2){0.f,0.f};
			app->projectiles[i].end_z = 0.f;
			app->projectiles_active++;
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
		app->projectiles[i].start = ft_vector2_add(app->projectiles[i].start,ft_vec2_mult(app->projectiles[i].end, app->conf->delta_time * app->projectile_def[app->projectiles[i].type - 11].speed));
		app->projectiles[i].start_z += app->projectiles[i].end_z * app->conf->delta_time * app->projectile_def[app->projectiles[i].type - 11].speed;
		if(app->projectiles[i].timer > 0)
			app->projectiles[i].timer -= app->conf->delta_time;
		else
			kill_projectile(app, &(app->projectiles[i]));
	}
}