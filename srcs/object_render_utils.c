/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:54:45 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/15 16:50:03 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Returns the texture size based on object type(pickups are small)
 * 
 * @param app 
 * @param id 
 * @return int 
 */
int	object_tex_size(t_app *app, int id)
{
	if (app->objects[id].type <= MAX_SMALL_OBJECTS)
	{
		return (TEX_PICKUP);
	}
	return (TEX_OBJECT);
}

/**
 * Returns radial direction of a vector.
 */
double	get_radial_direction(t_vector2 *vector)
{
	double	rad;

	rad = atan2(vector->x, vector->y);
	if (rad < 0)
		rad = rad + 2 * M_PI;
	return (rad);
}

/**
 * @brief Sets the object angled frame based on relation to player
 * 
 * @param app 
 * @param dir 
 * @param object 
 */
void	object_frame(t_app *app, t_vector2 dir, t_render_object *object)
{
	double	rad;

	object->frame = 0;
	if (app->objects[object->id].type <= MAX_OBJECT_TYPES)
	{
		rad = get_radial_direction(&dir);
			object->frame = ((int)((rad + app->objects[object->id].rot)
					/ PI_PI * SPRITE_ANGLES) % SPRITE_ANGLES);
	}
}

/**
 * @brief Clamps object draw areas to screen
 * 
 * @param object 
 */
void	init_draw_area(t_render_object *object)
{
	object->draw_start = object->start;
	clamp_int(&object->draw_start.x, 0, WIN_W - 1);
	clamp_int(&object->draw_start.y, 0, WIN_W - 1);
	clamp_int(&object->end.x, 0, WIN_W - 1);
	clamp_int(&object->end.y, 0, WIN_W - 1);
}

/**
 * @brief Objects check and draw the depth array
 * to see if they're occluded by walls or by other objects
 * 
 * @param app 
 * @param object 
 * @param window 
 * @param color 
 */
void	draw_object_pixel(t_app *app, t_render_object *object,
		t_point window, int color)
{
	if ((color & 0xFF000000) > 0)
	{
		put_pixel_to_surface_check(app, window, shade_depth(
				shade_color(color, object->light), object->dist), object->dist);
	}
}
