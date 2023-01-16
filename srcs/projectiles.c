/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:01:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 19:04:00 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool	sector_height(t_app *app, t_projectile *projectile,
		t_bool compare, double (*sector_function)(t_app *, int, t_vector2))
{
	t_vector2	end;
	t_vector2	heights;
	double		end_z;
	double		dist;

	heights.x = sector_function(app,projectile->sector, projectile->start);
	heights.y = sector_function(app, projectile->sector, projectile->end);
	dist = ft_point_distance(projectile->start, projectile->end);
	end_z = projectile->start_z + dist * projectile->end_z;
	if ((heights.y < end_z && compare) || (!compare && heights.y > end_z))
	{
		if (ft_line_intersection((t_line){(t_vector2){0.f, projectile->start_z},
				(t_vector2){dist, end_z}}, 
				(t_line){(t_vector2){0.f, heights.x},
				(t_vector2){dist, heights.y}}, &heights))
		{
			end = ft_vector2_add(projectile->start, ft_vector_resize(
					ft_vector2_sub(projectile->end, projectile->start),
					heights.x));
			if (inside_sector(app, projectile->sector, end))
			{
				projectile->end = end;
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

static t_bool sector_height_collision(t_app *app, t_projectile *projectile)
{
	if(sector_height(app, projectile, TRUE, sector_ceil_height)
			|| sector_height(app, projectile, FALSE, sector_floor_height))
		return (TRUE);
	return (FALSE);
}

t_bool projectile_member_check(t_app *app, t_projectile *projectile)
{
	int			i;
	t_vector2	intersection;
	double		tmp;
	t_line		wall_line;

	i = -1;
	while (++i < app->sectors[projectile->sector].corner_count)
	{
		wall_line = get_wall_line(app, projectile->sector, i);
		if (ft_line_side(wall_line, projectile->start))
			continue;
		if (ft_line_intersection_segment((t_line){projectile->start, projectile->end}, wall_line, &(intersection)))
		{
			tmp = ft_vector_length(ft_vector2_sub(intersection, projectile->start));
			tmp = projectile->start_z + tmp * projectile->end_z;
			if(portal_can_enter_(app, ft_vec2_to_vec3(intersection, tmp), 0.0f, wall_line, projectile->sector, app->sectors[projectile->sector].parent_sector))
			{
				projectile->sector = app->sectors[projectile->sector].parent_sector;
				return (TRUE);
			}
			else
			{
				projectile->end = intersection;
				return (FALSE);
			}
		}
	}
	return (FALSE);
}

static void	check_member_walls(t_app *app, t_projectile *projectile, int member_id)
{
	t_line		wall_line;
	double		dist;
	int			i;
	t_vector2	collision;

	i = -1;
	while (++i < app->sectors[member_id].corner_count)
	{
		wall_line = get_wall_line(app, member_id, i);
		if (ft_line_side(wall_line, projectile->end))
			continue;
		if(ft_line_intersection_segment((t_line){projectile->start, projectile->end}, wall_line, &(collision)))
		{
			dist = ft_vector_length(ft_vector2_sub(collision, projectile->start));
			if(!portal_can_enter_(app, ft_vec2_to_vec3(collision, projectile->start_z + dist * projectile->end_z), 0.0f, wall_line, projectile->sector, member_id))
			{
				projectile->end = collision;
				break;
			}
			else
			{
				projectile->sector = member_id;
				if(!projectile_member_check(app, projectile))
				{
					sector_height_collision(app, projectile);
					return ;
				}
				break;
			}
		}
	}
}

static t_bool	check_main_walls(t_app *app, t_projectile *projectile, int id)
{
	t_line		wall_line;
	double		dist;
	t_vector2	collision;

	wall_line = get_wall_line(app, projectile->sector, id);
		if (!ft_line_side(wall_line, projectile->end))
			return (TRUE);
		if (!ft_line_intersection_segment((t_line){projectile->start,
				projectile->end}, wall_line, &(collision)))
			return (TRUE);
		dist = ft_vector_length(ft_vector2_sub(collision, projectile->start));
		dist = projectile->start_z + dist * projectile->end_z;
		if(!portal_can_enter_(app, ft_vec2_to_vec3(collision, dist), 0.0f, wall_line, projectile->sector, app->sectors[projectile->sector].wall_types[id]))
		{
			projectile->end = collision;
			sector_height_collision(app, projectile);
		}
		else
		{
			projectile->sector = app->sectors[projectile->sector].wall_types[id];
			projectile_test(app, projectile, FALSE);
		}
		return (FALSE);
}

/**
 * @brief recursively check the entire flight path of a projectile when it's launched
 * 
 * @param app 
 * @param new 
 * @param projectile 
 * @param init 
 */
void	projectile_test(t_app *app, t_projectile *projectile, t_bool init)
{
	static int	recursion_count;
	int counter;

	if(init)
		recursion_count = 0;
	recursion_count++;
	if(recursion_count > MAX_VISIBLE_SECTORS)
		return ;
	if(app->sectors[projectile->sector].parent_sector == -1)
	{
		counter = -1;
		while(app->sectors[projectile->sector].member_sectors[++counter] != -1)
			check_member_walls(app, projectile, app->sectors[projectile->sector].member_sectors[counter]);
	}
	if(app->sectors[projectile->sector].parent_sector == -1)
			sector_height_collision(app, projectile);
	counter = -1;
	while (++counter < app->sectors[projectile->sector].corner_count)
	{
		if(check_main_walls(app, projectile, counter))
			continue;
		else
			return;
	}
}

/**
 * @brief calculate the end point of the projectile based on the direction
 * 
 * @param app 
 * @param projectile 
 * @param target_dir 
 */
static void calc_end(t_app *app, t_projectile *projectile, t_vector3 target_dir)
{
	t_move new;
	t_vector2	start;
	double		start_z;

	start = projectile->start;
	start_z = projectile->start_z;
	new.pos = ft_vector2_add(projectile->start, ft_vec2_mult((t_vector2){target_dir.x,target_dir.y}, 25.f));
	new.elevation = start_z;
	projectile->end = new.pos;
	projectile->end_z = target_dir.z;
	projectile_test(app, projectile, TRUE);
	projectile->start = start;
	projectile->start_z = start_z;
}



/**
 * @brief Fire calculates the entire lifetime of a projectile to later just render
 * info.x = type, info.y = sector
 * @param app 
 * @param target_dir 
 * @param start_pos 
 * @param info 
 */
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


/**
 * @brief Kills projectiles, specific types trigger other events(explosion at the end)
 * 
 * @param app 
 * @param projectile 
 */
void	kill_projectile(t_app *app, t_projectile *projectile)
{
			//event to explode creates a new melee attack type explosion
			if(projectile->type == 18)
				melee(app,(t_vector3){0.f,0.f,0.f}, ft_vec2_to_vec3(ft_vector2_sub(projectile->start, ft_vec2_mult(projectile->end, 0.15f)), projectile->start_z - projectile->end_z * 0.15f),(t_point){12,projectile->sector});
			projectile->type = -1;
			app->projectiles_active--;
}

/**
 * @brief Melee is the same as fire except it stays still for the duration of a timer 
 * 
 * @param app 
 * @param target_dir 
 * @param start_pos 
 * @param info 
 */
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
				app->projectiles[i].start = ft_vector2_add(app->projectiles[i].start, ft_vec2_mult(app->projectiles[i].end, 0.5f));
			app->projectiles[i].end = (t_vector2){0.f,0.f};
			app->projectiles[i].end_z = 0.f;
			app->projectiles_active++;
			return;
		}
	}
}

/**
 * @brief loops through the projectile array adds time to timers and updats positions
 * 
 * @param app 
 */
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