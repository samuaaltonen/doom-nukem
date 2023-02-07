/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_render_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 20:51:27 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/07 16:37:56 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Initializes values needed for rendering object sprites
 * 
 * @param app 
 * @param i 
 * @param object 
 * @param angle 
 * @return t_bool 
 */
static t_bool	init_object(t_app *app, int i, t_render_object *object,
		double *angle)
{
	t_vector2	vector;
	double		dist;
	t_vector2	transform;

	vector = ft_vector2_sub(app->objects[i].position, app->player.pos);
	dist = ft_vector_length(vector);
	if (dist > MAX_OBJECT_DISTANCE)
		return (FALSE);
	object->dist = dist * cos(ft_vector_angle(vector, app->player.dir));
	*angle = atan(fabs(app->player.elevation - app->objects[i].elevation)
			/ dist);
	if (*angle > 1.f || *angle < 0)
		return (FALSE);
	transform = ft_vector_multiply_matrix(vector,
			ft_matrix_inverse((t_matrix2){app->player.cam, app->player.dir}));
	if (transform.y / dist < 0.7f)
		return (FALSE);
	object->id = i;
	object->tex_size = object_tex_size(app, object->id);
	if (object->tex_size == TEX_PICKUP)
		transform = (t_vector2){transform.x / SMALL_SCALE,
			transform.y / SMALL_SCALE};
	object->size = (t_vector2){WIN_H / transform.y, WIN_H / transform.y};
	object->start.x = (int)((WIN_W / 2) * (1.0f + (transform.x / transform.y)));
	return (TRUE);
}

static t_bool	init_temp_object(t_app *app, int i, t_render_object *object,
		double *angle)
{
	t_vector2	vector;
	double		dist;
	t_vector2	transform;

	vector = ft_vector2_sub(app->bullets[i].start, app->player.pos);
	dist = ft_vector_length(vector);
	if (dist > MAX_OBJECT_DISTANCE)
		return (FALSE);
	object->dist = dist * cos(ft_vector_angle(vector, app->player.dir));
	*angle = atan(fabs(app->player.elevation - app->bullets[i].start_z)
			/ dist);
	if (*angle > 1.f || *angle < 0)
		return (FALSE);
	transform = ft_vector_multiply_matrix(vector,
			ft_matrix_inverse((t_matrix2){app->player.cam, app->player.dir}));
	if (transform.y / dist < 0.75f)
		return (FALSE);
	object->id = MAX_OBJECTS + i;
	object->tex_size = TEX_PICKUP;
	transform = (t_vector2){transform.x / SMALL_SCALE,
		transform.y / SMALL_SCALE};
	object->size = (t_vector2){WIN_H / transform.y, WIN_H / transform.y};
	object->start.x = (int)((WIN_W / 2) * (1.0f + (transform.x / transform.y)));
	return (TRUE);
}

/**
 * @brief Set the object values for rendering based on the initialized values
 * 
 * @param app 
 * @param object 
 * @param angle 
 * @param original_obj 
 */
static void	set_object(t_app *app, t_render_object *object, double *angle,
	t_gameobject *original_obj)
{
	double			offset;

	if (object->tex_size == TEX_PICKUP)
		object->start.y = (int)(WIN_H * app->player.horizon + object->size.y
				/ SMALL_SCALE * ((app->player.elevation + app->player.height)
					- (original_obj->elevation + SMALL_SCALE / 2)));
	else
		object->start.y = (int)(WIN_H * app->player.horizon + object->size.y
				* ((app->player.elevation + app->player.height)
					- (original_obj->elevation + 0.5)));
	offset = object->size.y;
	object->size.y = cos(*angle) * object->size.y;
	offset = (offset - object->size.y) / 2;
	object->start.y += (int)offset;
	object->end.x = object->start.x + object->size.x / 2;
	object->end.y = object->start.y + object->size.y / 2;
	object->start.x = object->start.x - object->size.x / 2;
	object->start.y = object->start.y - object->size.y / 2;
	object->light = app->sectors[original_obj->sector].light;
	object->step = (t_vector2){object->tex_size / (double)(object->size.x),
		object->tex_size / (double)(object->size.y)};
	object_frame(app,
		ft_vector2_sub(original_obj->position, app->player.pos), object);
	init_draw_area(object);
	app->objectstack.visible_count++;
}

static void	set_tmp_object(t_app *app, t_render_object *object, double *angle,
	t_bullet *original_obj)
{
	double			offset;

	if (object->tex_size == TEX_PICKUP)
		object->start.y = (int)(WIN_H * app->player.horizon + object->size.y
				/ SMALL_SCALE * ((app->player.elevation + app->player.height)
					- (original_obj->start_z)));
	else
		object->start.y = (int)(WIN_H * app->player.horizon + object->size.y
				* ((app->player.elevation + app->player.height)
					- (original_obj->start_z + 0.5)));
	offset = object->size.y;
	object->size.y = cos(*angle) * object->size.y;
	offset = (offset - object->size.y) / 2;
	object->start.y += (int)offset;
	object->end.x = object->start.x + object->size.x / 2;
	object->end.y = object->start.y + object->size.y / 2;
	object->start.x = object->start.x - object->size.x / 2;
	object->start.y = object->start.y - object->size.y / 2;
	object->light = app->sectors[original_obj->sector].light;
	object->step = (t_vector2){object->tex_size / (double)(object->size.x),
		object->tex_size / (double)(object->size.y)};
	object->frame = 0;
	init_draw_area(object);
	app->objectstack.visible_count++;
}

/**
 * @brief Adds all visible objects and bullets(temp objects)
 * to stack for drawing
 * 
 * @param app 
 */
void	objects_visible(t_app *app)
{
	int				i;
	t_render_object	*object;
	double			angle;

	i = -1;
	app->objectstack.visible_count = 0;
	while (++i < MAX_OBJECTS && app->objects[i].type != 0)
	{
		if (app->objects[i].type == -1 || !obj_seen(app, i))
			continue ;
		object = &(app->objectstack.objects[app->objectstack.visible_count]);
		if (!init_object(app, i, object, &angle))
			continue ;
		set_object(app, object, &angle, &(app->objects[i]));
	}
	i = -1;
	while (++i < MAX_TEMP_OBJECTS)
	{
		if (app->bullets[i].type == -1)
			continue ;
		object = &(app->objectstack.objects[app->objectstack.visible_count]);
		if (!init_temp_object(app, i, object, &angle))
			continue ;
		set_tmp_object(app, object, &angle, &(app->bullets[i]));
	}
}
