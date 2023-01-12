/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/12 18:21:11 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"


t_bool	in_range_height(double pos, double obj, double epsilon)
{
	if (pos > obj - epsilon
		&& pos < obj + epsilon)
		return (TRUE);
	return (FALSE);
}

t_bool	in_range(t_vector2 pos, t_vector2 obj, double epsilon)
{

	if (pos.x > obj.x - epsilon
		&& pos.x < obj.x + epsilon 
		&& pos.y > obj.y - epsilon
		&& pos.y < obj.y + epsilon)
		return (TRUE);
	return (FALSE);
}

static void	object_hit(t_app *app, t_gameobject *obj)
{
	if(obj->type == ARMOR_PICKUP)
		app->player.inventory.antidote++;
	else if(obj->type == HP_PICKUP)
		app->player.inventory.potion++;
	if(obj->type < MONSTER1)
		obj->type = -1;
}

static int	per_object_collision(t_app *app, t_vector2 pos, double elev, t_gameobject *obj)
{
	if (in_range(pos, obj->position, 0.5f) && in_range_height(elev, obj->elevation, PICKUP_RANGE))
	{
			object_hit(app, obj);
	}
	return (0);
}

static t_bool	line_collision(t_app *app, t_projectile *projectile, t_gameobject *obj)
{
	t_vector2	point;
	t_vector2	backwards;
	t_line		collision_line;

	backwards = ft_vector2_sub(projectile->start,
		ft_vec2_mult(projectile->end, -app->conf->delta_time));
	collision_line = (t_line){projectile->start, backwards};
	point = ft_closest_point(obj->position,collision_line);
	if (ft_point_on_segment(collision_line, point) && in_range(point, obj->position, PROJECTILE_COLLISION_X))
	{
		return (TRUE);
	}
	return (FALSE);
}

static int	projectile_obj_collision(t_app *app, t_projectile *projectile, t_gameobject *obj)
{
	(void)app;


	if(projectile->type > 12)
	{
		if((in_range(projectile->start, obj->position, PROJECTILE_COLLISION_X) || line_collision(app, projectile, obj))
				&& in_range_height(projectile->start_z, obj->elevation + 0.5f, PROJECTILE_COLLISION_Y))
			kill_projectile(app,projectile);
	}
	return (0);
}

void	projectile_player_collision(t_app *app)
{
	t_projectile	*projectile;
	int				i;


	projectile = &(app->projectiles[0]);
	i = app->projectiles_active;
	while (i > 0)
	{
		if(projectile->type != -1)
		{
			if(projectile->type < 15)
			{
				if(in_range( app->player.pos, projectile->start, app->projectile_def[projectile->type - 11].size.x) && in_range_height(app->player.elevation + app->player.height, projectile->start_z, app->projectile_def[projectile->type - 11].size.y))
				{
					//player take hit
					damage(app, app->projectile_def[projectile->type - 11].damage);
					kill_projectile(app, projectile);
				}
			}
			i--;
		}
		projectile++;
	}
}

void	object_collision(t_app *app)
{
	t_gameobject	*obj;
	t_projectile	*projectile;
	int				i;

	obj = &(app->objects[0]);
	while (obj->type != 0)
	{
		if(obj->type != -1)
		{
			per_object_collision(app, app->player.pos, app->player.elevation, obj);
			if(obj->type > MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
			{
				projectile = &(app->projectiles[0]);
				i = app->projectiles_active;
				while (i > 0)
				{
					if(projectile->type != -1)
					{
						projectile_obj_collision(app, projectile, obj);
						i--;
					}
					projectile++;
				}
			}
		}
		obj++;
	}
}

