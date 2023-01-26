/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_wall_collisions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:15:53 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/26 16:49:21 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool	bullet_member_check(t_app *app, t_bullet *bullet)
{
	int			i;
	t_vector2	collision;
	t_line		wall_line;

	i = -1;
	while (++i < app->sectors[bullet->sector].corner_count)
	{
		wall_line = get_wall_line(app, bullet->sector, i);
		if (ft_line_side(wall_line, bullet->start)
			|| !ft_line_intersection_segment((t_line){bullet->start,
				bullet->end}, wall_line, &(collision)))
			continue ;
		bullet->wall_id = i;
		if (projectile_can_enter(app, ft_vec2_to_vec3(collision, bullet->start_z
					+ ft_vector_length(ft_vector2_sub(collision, bullet->start))
					* bullet->end_z), bullet,
				app->sectors[bullet->sector].parent_sector))
		{
			bullet->sector = app->sectors[bullet->sector].parent_sector;
			return (TRUE);
		}
		bullet->end = collision;
		break ;
	}
	return (FALSE);
}

static void	check_member_walls(t_app *app, t_bullet *bullet, int id)
{
	int			i;
	t_vector2	collision;
	t_line		wall_line;

	i = -1;
	while (++i < app->sectors[id].corner_count)
	{
		wall_line = get_wall_line(app, id, i);
		if (ft_line_side(wall_line, bullet->end)
			|| !ft_line_intersection_segment((t_line){bullet->start,
				bullet->end}, wall_line, &(collision)))
			continue ;
		bullet->wall_id = i;
		if (!projectile_can_enter(app, ft_vec2_to_vec3(collision,
					bullet->start_z + ft_vector_length(ft_vector2_sub(collision,
							bullet->start)) * bullet->end_z), bullet, id))
			bullet->end = collision;
		else
		{
			bullet->sector = id;
			if (!bullet_member_check(app, bullet))
				return ((void)sector_height_collision(app, bullet));
		}
		break ;
	}
}

static t_bool	check_main_walls(t_app *app, t_bullet *bullet, int id)
{
	t_line		wall_line;
	double		dist;
	t_vector2	collision;

	wall_line = get_wall_line(app, bullet->sector, id);
	if (!ft_line_side(wall_line, bullet->end))
		return (TRUE);
	if (!ft_line_intersection_segment((t_line){bullet->start,
			bullet->end}, wall_line, &(collision)))
		return (TRUE);
	dist = ft_vector_length(ft_vector2_sub(collision, bullet->start));
	dist = bullet->start_z + dist * bullet->end_z;
	if (!projectile_can_enter(app, ft_vec2_to_vec3(collision, dist), bullet,
			app->sectors[bullet->sector].wall_types[id]))
	{
		bullet->end = collision;
		sector_height_collision(app, bullet);
	}
	else
	{
		bullet->sector = app->sectors[bullet->sector].wall_types[id];
		bullet_test(app, bullet, FALSE);
	}
	return (FALSE);
}

/**
 * @brief recursively check the entire flight path of a bullet when launched
 * 
 * @param app 
 * @param new 
 * @param bullet 
 * @param init 
 */
void	bullet_test(t_app *app, t_bullet *bullet, t_bool init)
{
	static int	recursion_count;
	int			counter;

	if (init)
		recursion_count = 0;
	recursion_count++;
	if (recursion_count > MAX_VISIBLE_SECTORS)
		return ;
	if (app->sectors[bullet->sector].parent_sector == -1)
	{
		counter = -1;
		while (app->sectors[bullet->sector].member_sectors[++counter] != -1)
			check_member_walls(app, bullet,
				app->sectors[bullet->sector].member_sectors[counter]);
	}
	if (app->sectors[bullet->sector].parent_sector == -1)
		sector_height_collision(app, bullet);
	counter = -1;
	while (++counter < app->sectors[bullet->sector].corner_count)
	{
		bullet->wall_id = counter;
		if (!check_main_walls(app, bullet, counter))
			return ;
	}
}

/**
 * @brief calculate the end point of the bullet based on the direction
 * 
 * @param app 
 * @param bullet 
 * @param target_dir 
 */
void	calc_end(t_app *app, t_bullet *bullet, t_vector3 target_dir)
{
	t_vector2	start;
	double		start_z;

	start = bullet->start;
	start_z = bullet->start_z;
	bullet->end = ft_vector2_add(bullet->start,
			ft_vec2_mult((t_vector2){target_dir.x, target_dir.y}, 25.f));
	bullet->end_z = target_dir.z;
	bullet_test(app, bullet, TRUE);
	bullet->start = start;
	bullet->start_z = start_z;
}
