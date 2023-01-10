/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:02:49 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/10 15:51:12 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"


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

static void	object_frame(t_app *app, t_vector2 dir, t_render_object *object)
{
	double	rad;

	object->frame = 0;
	if(app->objects[object->id].type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES)
	{
		rad = get_radial_direction(&dir);
			object->frame = ((int)((rad + app->objects[object->id].rot) / PI_PI * SPRITE_ANGLES) % SPRITE_ANGLES);
	}

}

void	draw_object_pixel(t_app *app, t_render_object *object, t_point window, t_vector2 texture)
{
	int	color;
	int	object_type;

	if(object->id >= MAX_OBJECTS)
		object_type = app->projectiles[object->id - MAX_OBJECTS].type;
	else
		object_type = app->objects[object->id].type;
	color = 0xFFFFFFFF;
	if(object_type <= MAX_SMALL_OBJECTS)
		color = get_pixel_color(app->assets.sprites[SMALL_SPRITE],
			(int)texture.x + ((SPRITE_ANGLES - object->frame - 1) * object->tex_size),
			(int)texture.y + (object_type - 1) * object->tex_size);
	else if(object_type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS)
		color = get_pixel_color(app->assets.sprites[BIG_SPRITE],
			(int)texture.x + ((SPRITE_ANGLES - object->frame - 1) * object->tex_size),
			(int)texture.y + (object_type - MAX_SMALL_OBJECTS - 1) * object->tex_size);
	else if(object_type <= MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES)
		color = get_pixel_color(app->assets.sprites[ENEMY_SPRITE + object_type - (MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + 1)],
			(int)texture.x + ((SPRITE_ANGLES - object->frame - 1) * object->tex_size),
			(int)(texture.y + (ft_abs((int)app->object_states[object->id]) * object->tex_size)));
	else if(object_type > MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES)
	{
		//ft_printf("object_type %i\n", object_type - MAX_SMALL_OBJECTS + MAX_BIG_OBJECTS + MAX_ENEMY_TYPES - 1);
		color = get_pixel_color(app->assets.sprites[PROJECTILE_SPRITE],
			(int)texture.x,
			(int)texture.y + (object_type - MAX_SMALL_OBJECTS - MAX_BIG_OBJECTS - MAX_ENEMY_TYPES - 1) * TEX_PICKUP);
	}
	if ((color & 0xFF000000) > 0)
		//put_pixel_to_surface(app->surface, window.x, window.y,color);
		put_pixel_to_surface_check(app, window,color,object->dist);
}

static void	init_draw_area(t_render_object *object)
{
	object->draw_start = object->start;
	if (object->draw_start.x < 0)
		object->draw_start.x = 0;
	if (object->draw_start.y < 0)
		object->draw_start.y = 0;
	if (object->end.x >= WIN_W)
		object->end.x = WIN_W - 1;
	if (object->end.y >= WIN_H)
		object->end.y = WIN_H - 1;
}

void	object_render(t_app *app, t_render_object *object, t_thread_data *thread)
{
	int x;
	int y;
	
	t_vector2	texture_pixel;
	
	texture_pixel = (t_vector2){(object->draw_start.x - object->start.x) * object->step.x,0.f};

	x = object->draw_start.x;
	while(++x < object->end.x)
	{
		if(x % THREAD_COUNT != thread->id)
		{
			texture_pixel.x += object->step.x;
			continue;
		}
		y = object->draw_start.y;
		texture_pixel.y = (object->draw_start.y - object->start.y) * object->step.y;
		while (++y <  object->end.y)
		{
			draw_object_pixel(app, object, (t_point){x, y}, texture_pixel);
			texture_pixel.y += object->step.y;
		}
		texture_pixel.x +=object->step.x;
	}
}

void	objects_render(t_app *app, t_thread_data *thread)
{
	int	i;
	i = 0;

	while(i < app->objectstack.visible_count)
	{
		object_render(app, &(app->objectstack.objects[i]), thread);	
		i++;
	}
}

void	*object_render_thread(void *data)
{
	t_app			*app;
	t_thread_data	*thread;

	thread = (t_thread_data *)data;
	app = (t_app *)thread->app;
	while (TRUE)
	{
		if (pthread_mutex_lock(&thread->lock))
			exit_error(NULL);
		while (!thread->has_work)
			if (pthread_cond_wait(&thread->cond, &thread->lock))
				exit_error(NULL);
		objects_render(app, thread);
		thread->has_work = FALSE;
		if (pthread_mutex_unlock(&thread->lock))
			exit_error(NULL);
	}
	pthread_exit(NULL);
}

static int	object_tex_size(t_app *app, int id)
{
	if(app->objects[id].type <= MAX_SMALL_OBJECTS)
	{
		return (TEX_PICKUP);
	}
	return (TEX_OBJECT);
}

static t_bool	init_object(t_app *app, int i, t_render_object *object,
		double *angle)
{
	t_vector2	vector;
	double		dist;
	t_vector2	transform;

	vector = ft_vector2_sub(app->objects[i].position, app->player.pos);
	dist = ft_vector_length(vector);
	if(dist > MAX_OBJECT_DISTANCE)
		return (FALSE);
	object->dist = dist * cos(ft_vector_angle(vector, app->player.dir));
	*angle = atan(fabs(app->player.elevation - app->objects[i].elevation)
			/ dist);
	if(*angle > 1.f || *angle < 0)
		return (FALSE);

	transform = ft_vector_multiply_matrix(vector,
	ft_matrix_inverse((t_matrix2){app->player.cam, app->player.dir}));
	if(transform.y / dist < 0.75f)
		return (FALSE);
	object->id = i;
	object->tex_size = object_tex_size(app, object->id);
	if(object->tex_size == TEX_PICKUP)
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

	vector = ft_vector2_sub(app->projectiles[i].start, app->player.pos);
	dist = ft_vector_length(vector);
	if(dist > MAX_OBJECT_DISTANCE)
		return (FALSE);
	object->dist = dist * cos(ft_vector_angle(vector, app->player.dir));
	*angle = atan(fabs(app->player.elevation - app->projectiles[i].start_z)
			/ dist);
	if(*angle > 1.f || *angle < 0)
		return (FALSE);
	transform = ft_vector_multiply_matrix(vector,
	ft_matrix_inverse((t_matrix2){app->player.cam, app->player.dir}));
	if(transform.y / dist < 0.75f)
		return (FALSE);
	object->id = MAX_OBJECTS + i;
	object->tex_size = TEX_PICKUP;
	transform = (t_vector2){transform.x / SMALL_SCALE, transform.y / SMALL_SCALE};
	object->size = (t_vector2){WIN_H / transform.y, WIN_H / transform.y};
	object->start.x = (int)((WIN_W / 2) * (1.0f + (transform.x / transform.y)));
	return (TRUE);
}

static void	set_object(t_app *app, t_render_object *object, double *angle,
	t_gameobject *original_obj)
{
		double			offset;

		if(object->tex_size == TEX_PICKUP)
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
		object->step = (t_vector2){object->tex_size / (double)(object->size.x),
				object->tex_size / (double)(object->size.y)};
		object_frame(app,
				ft_vector2_sub(original_obj->position,app->player.pos), object);
		init_draw_area(object);
		app->objectstack.visible_count++;
}

static void	set_tmp_object(t_app *app, t_render_object *object, double *angle,
	t_projectile *original_obj)
{
		double			offset;

		if(object->tex_size == TEX_PICKUP)
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
		object->step = (t_vector2){object->tex_size / (double)(object->size.x),
				object->tex_size / (double)(object->size.y)};
		object->frame = 0;
		init_draw_area(object);
		app->objectstack.visible_count++;
}

//list all visible objects
static void	objects_visible(t_app *app)
{
	int				i;
	t_render_object	*object;
	double			angle;

	i = -1;
	app->objectstack.visible_count = 0;
	while (++i < MAX_OBJECTS)
	{
		if(app->objects[i].type == 0)
			break;
		if(app->objects[i].type == -1)
			continue;
		object = &(app->objectstack.objects[app->objectstack.visible_count]);
		if (!init_object(app, i,object,&angle))
			continue;
		set_object(app, object, &angle, &(app->objects[i]));
	}
	i = -1;
	while (++i < MAX_TEMP_OBJECTS) //temp objects
	{
		if(app->projectiles[i].type == -1)
			continue;
		object = &(app->objectstack.objects[app->objectstack.visible_count]);
		if (!init_temp_object(app, i,object,&angle))
			continue;
		set_tmp_object(app, object, &angle, &(app->projectiles[i]));
	}
}


void	render_objects(t_app *app)
{
	static t_thread_data	threads_data[THREAD_COUNT];
	static t_bool			threads_created;

	if (!threads_created)
	{
		threads_init(app, (t_thread_data *)&threads_data);
		threads_create((t_thread_data *)&threads_data, object_render_thread);
		threads_created = TRUE;
	}
	objects_visible(app);
	threads_work((t_thread_data *)&threads_data);
	
}