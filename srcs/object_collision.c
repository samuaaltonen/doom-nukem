/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:17:11 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 14:30:48 by ssulkuma         ###   ########.fr       */
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
	if (obj->type == ARMOR_PICKUP)
		app->player.inventory.armor_pack++;
	else if (obj->type == COIN_PICKUP)
		app->player.inventory.key++;
	else if (obj->type == AMMO_PICKUP)
		app->player.inventory.ammo += AMMO_PICKUP_AMOUNT;
	else if (obj->type == HP_PICKUP)
		app->player.inventory.potion++;
	else if (obj->type == JETPACK_PICKUP)
		app->player.inventory.jetpack = TRUE;
	else if (obj->type == WEAPON1)
		app->player.weapons |= 0b00000001;
	else if (obj->type == WEAPON2)
		app->player.weapons |= 0b00000010;
	if (obj->type <= MAX_SMALL_OBJECTS)
	{
		obj->type = -1;
		interaction_by_pickup(app, obj);
	}
}

static int	per_object_collision(t_app *app, t_vector2 pos, double elev,
	t_gameobject *obj)
{
	if (in_range(pos, obj->position, 0.5f)
		&& in_range_height(elev, obj->elevation, PICKUP_RANGE))
	{
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
		if (obj->type != -1 && obj->type <= MAX_SMALL_OBJECTS)
			per_object_collision(app, app->player.pos,
				app->player.elevation, obj);
		obj++;
	}
}
