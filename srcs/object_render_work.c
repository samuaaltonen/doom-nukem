/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_work.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:59:50 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 21:05:20 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	object_render(t_app *app, t_render_object *object,
	t_thread_data *thread, t_vector2 (*f)(
		t_app *, t_render_object *, t_vector2, int *))
{
	int			x;
	int			y;
	t_vector2	texture_pixel;
	t_vector2	texture_start;
	int			sprite_id;

	texture_start = f(app, object,
			(t_vector2){(object->draw_start.x - object->start.x)
			* object->step.x, (object->draw_start.y - object->start.y)
			* object->step.y}, &sprite_id);
	texture_pixel = texture_start;
	x = object->draw_start.x;
	while (++x < object->end.x)
	{
		if (x % THREAD_COUNT != thread->id)
		{
			texture_pixel.x += object->step.x;
			continue ;
		}
		y = object->draw_start.y;
		texture_pixel.y = texture_start.y;
		while (++y < object->end.y)
		{
			draw_object_pixel(app, object, (t_point){x, y},
				get_pixel_color(app->assets.sprites[sprite_id],
					(int)(texture_pixel.x), (int)(texture_pixel.y)));
			texture_pixel.y += object->step.y;
		}
		texture_pixel.x += object->step.x;
	}
}
