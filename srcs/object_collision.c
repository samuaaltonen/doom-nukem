/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/02 16:49:36 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_bool in_range(t_app *app, t_vector2 obj_pos, int epsilon)
{

	if (app->player.pos.x > obj_pos.x - epsilon
		&& app->player.pos.x < obj_pos.x + epsilon 
		&& app->player.pos.y > obj_pos.y - epsilon
		&& app->player.pos.y < obj_pos.y + epsilon)
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

static int	per_object_collision(t_app *app, t_gameobject *obj)
{
	if (in_range(app, obj->position, 2))
	{
		if (ft_point_distance(app->player.pos, obj->position) + app->player.elevation - obj->elevation < 0.5f)
			object_hit(app, obj);
	}
	return (0);
}

void	object_collision(t_app *app)
{
	t_gameobject	*obj;

	obj = &(app->objects[0]);
	while (obj->type != 0)
	{
		if(obj->type != -1)
			per_object_collision(app, obj);
		obj++;
	}
}

