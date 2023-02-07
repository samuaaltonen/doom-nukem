/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:02:49 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 16:46:20 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static t_vector2	render_small(t_app *app, t_render_object *object,
	t_vector2 tex, int *sprite_id)
{
	*sprite_id = SMALL_SPRITE;
	tex.x += ((SPRITE_ANGLES - object->frame - 1) * object->tex_size);
	tex.y += (app->objects[object->id].type - 1) * object->tex_size;
	return (tex);
}

static t_vector2	render_big(t_app *app, t_render_object *object,
	t_vector2 tex, int *sprite_id)
{
	*sprite_id = BIG_SPRITE;
	tex.x += ((SPRITE_ANGLES - object->frame - 1) * object->tex_size);
	tex.y += (app->objects[object->id].type
			- MAX_SMALL_OBJECTS - 1) * object->tex_size;
	return (tex);
}

static t_vector2	render_enemy(t_app *app, t_render_object *object,
	t_vector2 tex, int *sprite_id)
{
	*sprite_id = ENEMY_SPRITE_1 + app->objects[object->id].type
		- (MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + 1);
	tex.x += ((SPRITE_ANGLES - object->frame - 1) * object->tex_size);
	tex.y += (ft_abs((int)app->object_states[object->id]) * object->tex_size);
	return (tex);
}

static t_vector2	render_bullet(t_app *app, t_render_object *object,
	t_vector2 tex, int *sprite_id)
{
	*sprite_id = PROJECTILE_SPRITE;
	tex.x += 0.f;
	tex.y += (app->bullets[object->id - MAX_OBJECTS].type - 1) * TEX_PICKUP;
	return (tex);
}

/**
 * @brief Calls different renderers based on the object type
 * which initialize the correct spritesheet offsets
 * 
 * @param app 
 * @param thread 
 */
void	objects_render(t_app *app, t_thread_data *thread)
{
	int	i;
	int	object_type;

	i = 0;
	while (i < app->objectstack.visible_count)
	{
		object_type = app->objects[app->objectstack.objects[i].id].type;
		if (app->objectstack.objects[i].id >= MAX_OBJECTS)
			object_type = app->bullets[app->objectstack.objects[i].id
				- MAX_OBJECTS].type + MAX_OBJECT_TYPES;
		if (object_type <= MAX_SMALL_OBJECTS)
			object_render(app, &(app->objectstack.objects[i]), thread,
				render_small);
		else if (object_type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
			object_render(app, &(app->objectstack.objects[i]), thread,
				render_big);
		else if (object_type <= MAX_OBJECT_TYPES)
			object_render(app, &(app->objectstack.objects[i]), thread,
				render_enemy);
		else if (object_type > MAX_OBJECT_TYPES)
			object_render(app, &(app->objectstack.objects[i]), thread,
				render_bullet);
		i++;
	}
}
