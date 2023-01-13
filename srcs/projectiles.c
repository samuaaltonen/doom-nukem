/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:01:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/13 19:25:28 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"


static int	floor_collision(t_app *app, t_projectile *projectile)
{
	t_vector2 point;
	t_vector2 end;
	t_vector2 heights;
	t_vector2 intersection;
	double		end_z;
	double		dist;

	point = projectile->start;
	heights.x = sector_floor_height(app,projectile->sector, point);
	end = projectile->end;
	heights.y = sector_floor_height(app, projectile->sector, end);
	dist = ft_point_distance(projectile->start, projectile->end);
	end_z = projectile->start_z + dist * projectile->end_z;
	if(heights.y > end_z)
	{
		if (ft_line_intersection_segment((t_line){(t_vector2){0.f, projectile->start_z}, (t_vector2){dist, end_z}},
						(t_line){(t_vector2){0.f, heights.x},(t_vector2){dist, heights.y}}, &intersection))
		{
			projectile->end = ft_vector2_add(projectile->start,ft_vector_resize(ft_vector2_sub(projectile->end, projectile->start),intersection.x));
			return (1);
		}
	}
	return (0);
}

static int	ceil_collision(t_app *app, t_projectile *projectile)
{
	t_vector2 point;
	t_vector2 end;
	t_vector2 heights;
	t_vector2 intersection;
	double		end_z;
	double		dist;

	point = projectile->start;
	heights.x = sector_ceil_height(app,projectile->sector, point);
	end = projectile->end;
	heights.y = sector_ceil_height(app, projectile->sector, end);
	dist = ft_point_distance(projectile->start, projectile->end);
	end_z = projectile->start_z + dist * projectile->end_z;
	if(heights.y < end_z)
	{
		if (ft_line_intersection((t_line){(t_vector2){0.f, projectile->start_z}, (t_vector2){dist, end_z}},
						(t_line){(t_vector2){0.f, heights.x},(t_vector2){dist, heights.y}}, &intersection))
		{
			projectile->end = ft_vector2_add(projectile->start,ft_vector_resize(ft_vector2_sub(projectile->end, projectile->start),intersection.x));
			return (1);
		}
	}
	return (0);
}

static t_bool sector_height_collision(t_app *app, t_projectile *projectile)
{
	if(ceil_collision(app, projectile) || floor_collision(app, projectile))
		return (TRUE);
	return (FALSE);
}

t_bool	projectile_member_check(t_app *app, t_projectile *projectile)
{
	int	i;
	t_line		wall_line;
	t_vector2	intersection;

	//ft_printf("projectile end x%f,y%f, start x%f,y%f\n",projectile->end.x, projectile->end.y, projectile->start.x, projectile->start.y);

	i = -1;
	while (++i < app->sectors[projectile->sector].corner_count)
	{
		wall_line = get_wall_line(app, projectile->sector, i);
		if(!ft_line_side(wall_line, projectile->end))
			continue;
		if(ft_line_intersection_segment((t_line){projectile->start, projectile->end}, wall_line, &(intersection)))
		{
			double dist = ft_vector_length(ft_vector2_sub(intersection, projectile->start));
			if(portal_can_enter_(app, ft_vec2_to_vec3(intersection, projectile->start_z + dist * projectile->end_z), 0.0f, wall_line, projectile->sector, app->sectors[projectile->sector].parent_sector))
			{
				projectile->start_z = projectile->start_z + dist * projectile->end_z;
				projectile->start = intersection;
				projectile->sector = app->sectors[projectile->sector].parent_sector;
				return (TRUE);
			}
			else
			{
				projectile->end = intersection;
				sector_height_collision(app, projectile);
				return (FALSE);
			}
		}
	}
	if(sector_height_collision(app, projectile))
		return (FALSE);
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
//member sector walls
	if(app->sectors[projectile->sector].parent_sector == -1)
	{
		counter = 0;
		while(app->sectors[projectile->sector].member_sectors[counter] >= 0)
		{
			i = -1;
			member_id = app->sectors[projectile->sector].member_sectors[counter];
			while (++i < app->sectors[member_id].corner_count)
			{
				wall_line = get_wall_line(app, member_id, i);
				if(!ft_line_side(wall_line, new->pos) && ft_line_intersection_segment((t_line){projectile->start, new->pos}, wall_line, &(projectile->end)))
				{
					double dist = ft_vector_length(ft_vector2_sub(projectile->end, projectile->start));
					projectile->start_z = projectile->start_z + dist * projectile->end_z;
					if(!portal_can_enter_(app, ft_vec2_to_vec3(projectile->end, projectile->start_z), 0.0f, wall_line, projectile->sector, member_id))
					{
						projectile->start_z = new->elevation;
						sector_height_collision(app, projectile);
						return ;
					}
					projectile->start = projectile->end;
					projectile->end = new->pos;
					projectile->sector = member_id;
					if(projectile_member_check(app, projectile))
						projectile_flight(app, new, projectile, FALSE);
					return ;
				}
			}
			counter++;
		}
	}

	i = -1;
	while (++i < app->sectors[projectile->sector].corner_count)
	{
		projectile->end = new->pos;
		wall_line = get_wall_line(app, projectile->sector, i);
		if (!ft_line_side(wall_line, new->pos))
			continue ;
		if (!ft_line_intersection_segment((t_line){projectile->start, new->pos}, wall_line, &(projectile->end)))
			continue ;
		if(sector_height_collision(app, projectile))
			return ;
		if (app->sectors[projectile->sector].wall_types[i] < 0 || app->sectors[projectile->sector].wall_textures[i] == PARTIALLY_TRANSPARENT_TEXTURE_ID)
			return ;
		double dist = ft_vector_length(ft_vector2_sub(projectile->end, projectile->start));
		projectile->start_z = projectile->start_z + dist * projectile->end_z;
		if(!portal_can_enter_(app, ft_vec2_to_vec3(projectile->end, projectile->start_z), 0.0f, wall_line, projectile->sector, app->sectors[projectile->sector].wall_types[i]))
			return ;
		projectile->start = projectile->end;
		projectile->end = new->pos;
		projectile->sector = app->sectors[projectile->sector].wall_types[i];
		projectile_flight(app, new, projectile, FALSE);
		return ;
	}
		if(sector_height_collision(app, projectile))
			return ;
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
	projectile->end_z = target_dir.z;
	projectile_flight(app, &new, projectile, TRUE);
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