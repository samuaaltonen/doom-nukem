/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_work.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:59:50 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 16:40:56 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Calculates drawing start position.
 * 
 * @param object 
 * @return t_vector2 
 */
static t_vector2	get_draw_start(t_render_object *object)
{
	return ((t_vector2){(object->draw_start.x
			- object->start.x) * object->step.x, (object->draw_start.y
			- object->start.y) * object->step.y});
}

/**
 * @brief Each thread draws their own columns of each object
 * 
 * @param app 
 * @param object 
 * @param thread 
 * @param f 
 */
void	object_render(t_app *app, t_render_object *object,
	t_thread_data *thread, t_vector2 (*f)(
		t_app *, t_render_object *, t_vector2, int *))
{
	t_point		coord;
	t_vector2	pixel;
	t_vector2	texture_start;
	int			sprite_id;

	texture_start = f(app, object, get_draw_start(object), &sprite_id);
	pixel = texture_start;
	coord.x = object->draw_start.x;
	while (++coord.x < object->end.x)
	{
		if (coord.x % THREAD_COUNT != thread->id)
		{
			pixel.x += object->step.x;
			continue ;
		}
		coord.y = object->draw_start.y;
		pixel.y = texture_start.y;
		while (++coord.y < object->end.y)
		{
			draw_object_pixel(app, object, coord, get_pixel_color(app->assets.\
				sprites[sprite_id], (int)(pixel.x), (int)(pixel.y)));
			pixel.y += object->step.y;
		}
		pixel.x += object->step.x;
	}
}
