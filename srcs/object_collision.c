/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/12 19:44:51 by htahvana         ###   ########.fr       */
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

static t_bool	line_collision(t_app *app, t_projectile *projectile, t_enemy_state *enemy)
{
	t_vector2	point;
	t_vector2	backwards;
	t_line		collision_line;

	backwards = ft_vector2_sub(projectile->start,
		ft_vec2_mult(projectile->end, -app->conf->delta_time));
	collision_line = (t_line){projectile->start, backwards};
	point = ft_closest_point(app->objects[enemy->id].position,collision_line);
	if (ft_point_on_segment(collision_line, point) && in_range(point, app->objects[enemy->id].position, app->projectile_def[projectile->type - 11].size.x))
	{
		return (TRUE);
	}
	return (FALSE);
}


static void	damage_enemy(t_app *app, int damage, t_enemy_state *enemy)
{
	if(enemy->hp > damage)
		enemy->hp -= damage;
	else
	{
		enemy->hp = 0.f;
		enemy->state = DEATH;
		app->object_states[enemy->id] = app->enemy_def[app->objects[enemy->id].type - MONSTER1].states[enemy->state][0];
	}
}

static int	projectile_enemy_collision(t_app *app, t_projectile *projectile, t_enemy_state *enemy)
{
	if(projectile->type > 12)
	{
		if(!enemy->dead && (in_range(projectile->start, app->objects[enemy->id].position, app->projectile_def[projectile->type - 11].size.x) || line_collision(app, projectile, enemy))
				&& in_range_height(projectile->start_z, app->objects[enemy->id].elevation + 0.5f, app->projectile_def[projectile->type - 11].size.y))
		{
			damage_enemy(app, app->projectile_def[projectile->type - 11].damage, enemy);
			kill_projectile(app,projectile);
		}
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

	obj = &(app->objects[0]);
	while (obj->type != 0)
	{
		if(obj->type != -1)
		{
			per_object_collision(app, app->player.pos, app->player.elevation, obj);
		}
		obj++;
	}
}

void	bullet_enemy_collisions(t_app *app)
{
	t_projectile	*projectile;
	t_enemy_state	*enemy;
	int				i;

	enemy = &(app->enemies[0]);
	while (enemy->id != -1)
	{
		if(in_range(app->objects[enemy->id].position,app->player.pos, 25.f))
		{
			projectile = &(app->projectiles[0]);
			i = app->projectiles_active;
			while (i > 0)
			{
				if(projectile->type != -1)
				{
					projectile_enemy_collision(app, projectile, enemy);
					i--;
				}
				projectile++;
			}
		}
		enemy++;
	}
}

