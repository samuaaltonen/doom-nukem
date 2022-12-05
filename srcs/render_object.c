/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:02:49 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/05 13:49:03 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	draw_object_pixel(t_app *app, t_render_object *object, t_point window, t_vector2 texture)
{
	int	color;

	color = get_pixel_color(app->assets.sprites[object->id], (int)texture.x, (int)texture.y);
	if ((color & 0xFF000000) > 0)
		put_pixel_to_surface_check(app, window,color,object->dist);
		//put_pixel_to_surface(app->surface, window.x, window.y, color);
}

void	object_render(t_app *app, t_render_object *object, t_thread_data *thread)
{
	int x;
	int y;
	
	t_vector2	texture_pixel;
	
	texture_pixel = (t_vector2){0.f,0.f};

	x = object->start.x;
	/* ft_printf("Test, draw_start x%i, draw_end x%i\n", object->start.x, draw_end.x);
	ft_printf("Test, size x%f, y%f\n", object->size.x, object->size.y);
	ft_printf("Test, draw_start y%i, draw_end y%i\n", object->start.y, draw_end.y);
	ft_printf("Test, Step %f", object->step); */
	while(++x < object->draw_end.x)
	{
		if(x % THREAD_COUNT != thread->id)
		{
			texture_pixel.x +=object->step.x;
			continue;
		}
		y = object->start.y;
		texture_pixel.y = 0.f;
		while (++y <  object->draw_end.y)
		{
			//put_pixel_to_surface(app->surface, x, y, get_pixel_color(app->assets.sprites[object->id], (int)texture_pixel.x, (int)texture_pixel.y));
			//if(y % 2 == !app->depthmap_fill_switch)
				draw_object_pixel(app, object, (t_point){x, y}, texture_pixel);
			texture_pixel.y += object->step.y;
		}
		texture_pixel.x +=object->step.x;
	}
}
/**
 * Clamps distance to maximum distance.
 */
void	clamp_distance(double *distance)
{
	if (*distance > MAX_LINE_LENGTH)
		*distance = MAX_LINE_LENGTH;
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

//list all visible objects
static void	objects_visible(t_app *app)
{
	int				i;
	double			dist;
	t_vector2		vector;
	t_vector2		transform;
	t_render_object	*object;

	i = -1;
	app->objectstack.visible_count = 0;
	while (++i < MAX_OBJECTS)
	{
		if(app->objects[i].type == 0)
			continue;
		vector = ft_vector2_sub(app->objects[i].position, app->player.pos);
		dist = ft_vector_length(vector);

		if(dist < 15.f)
		{
				transform = ft_vector_multiply_matrix(vector,
				ft_matrix_inverse((t_matrix2){
					app->player.cam,
					app->player.dir
			}));
			if(transform.y / dist < 0.75f)
				continue;
			object = &(app->objectstack.objects[app->objectstack.visible_count]);

			double scale = (fabs(app->player.elevation - app->objects[i].elevation)) / (20);
			double angle = atan(fabs(app->player.elevation - app->objects[i].elevation) / dist) * RADIAN_IN_DEG;
			//new_value = (old_value - old_bottom) / (old_top - old_bottom) * (new_top - new_bottom) + new_bottom;
			if(angle > 60 || angle < 0)
				continue;
			object->size.x  = ft_abs((int)(WIN_H / transform.y));
			object->size.y  = ft_abs((int)(WIN_H / transform.y));
			ft_printf("scale %f angle %f", scale, angle);
			object->start.x = (int)((WIN_W / 2) * (1.0f + (transform.x / transform.y)));
			object->start.y = (int)(WIN_H * app->player.horizon + object->size.y * (app->player.elevation + app->player.height - (app->objects[i].elevation + (0.5))));
			object->draw_end.x = object->size.x / 2 + object->start.x;
			object->draw_end.y = object->start.y + object->size.y;
			object->dist = dist * cos(ft_vector_angle(vector, app->player.dir));
			object->start.x = object->start.x - object->size.x / 2;
			object->start.y = object->start.y - object->size.y / 2;
			object->step.x = TEX_SIZE / (double)(object->size.x);
			object->step.y = TEX_SIZE / (double)(object->size.y);
			app->objectstack.visible_count++;
			ft_printf("object data dist %f, start.y %i, transform y%f, elev %f, player elev %f, object y size %f", object->dist, object->start.y, transform.y / dist, app->objects[i].elevation, (app->player.elevation + app->player.height), object->size.y);
		}
	}
	ft_printf("objects found %i\n", app->objectstack.visible_count);
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
/* 	for(int i = 0;i < 5;i++)
	{
		ft_printf("stack obj dist %f, pos x%f,y%f, size x%f,y%f\n",app->objectstack.objects[i].dist, app->objectstack.objects[i].start.x, app->objectstack.objects[i].start.y, app->objectstack.objects[i].size.x, app->objectstack.objects[i].size.y);
	} */
	threads_work((t_thread_data *)&threads_data);
	
}