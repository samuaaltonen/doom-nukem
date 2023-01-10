/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/10 13:42:12 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"


t_bool	in_range_height(double pos, double obj, double epsilon)
{
	if (pos > obj - epsilon
		&& pos < pos + epsilon)
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

static int	per_object_collision(t_app *app, t_gameobject *obj)
{
	if (in_range(app->player.pos, obj->position, 2))
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

