/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:02:49 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/30 17:00:15 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	object_render(t_app *app, int index, t_thread_data *thread)
{
	int x;
	int y;

	x = app->objectstack.objects[index].start.x;
	while(++x < app->objectstack.objects[index].end.x)
	{
		if(x%4 != thread->id)
			continue;
		y = app->objectstack.objects[index].start.y;
		while (++y <  app->objectstack.objects[index].end.y)
			put_pixel_to_surface(app->surface,x,y, 2450 * (index + 1));
	}
}

void	objects_render(t_app *app, t_thread_data *thread)
{
	int	i;
	i = 0;

	while(i < app->objectstack.visible_count)
	{
		object_render(app, i, thread);	
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
	int	i;
	double	dist;
	t_vector2 difference;
	t_vector2 transform;

	i = -1;
	app->objectstack.visible_count = 0;
	while (++i < MAX_OBJECTS)
	{
		if(app->objects[i].type == 0)
			continue;
		difference = ft_vector2_sub(app->player.pos, app->objects[i].position);
		dist = ft_vector_length(difference);
		if(dist < 5.f)
		{
				transform = ft_vector_multiply_matrix(difference,
				ft_matrix_inverse((t_matrix2){
					app->player.cam,
					app->player.dir
			}));
			app->objectstack.objects[app->objectstack.visible_count].st = ft_abs((int)(WIN_H / transform.y));
			app->objectstack.objects[app->objectstack.visible_count].dist = dist;
			app->objectstack.visible_count++;
		}
	}
	ft_printf("objects found %i\n", app->objectstack.visible_count);
}


void	render_objects(t_app *app)
{
	static t_thread_data	threads_data[4];
	static t_bool			threads_created;

	if (!threads_created)
	{
		threads_init(app, (t_thread_data *)&threads_data);
		threads_create((t_thread_data *)&threads_data, object_render_thread);
		threads_created = TRUE;
	}
	objects_visible(app);
	for(int i = 0;i < 5;i++)
	{
		ft_printf("stack obj dist %f, pos x%f,y%f, size x%f,y%f\n",app->objectstack.objects[i].dist, app->objectstack.objects[i].pos.x, app->objectstack.objects[i].pos.y, app->objectstack.objects[i].size.x, app->objectstack.objects[i].size.y);
	}
	threads_work((t_thread_data *)&threads_data);
	
}