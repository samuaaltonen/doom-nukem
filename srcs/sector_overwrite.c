/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_overwrite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:51:12 by saaltone          #+#    #+#             */
/*   Updated: 2022/11/23 17:14:43 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	sector_render_overwrite_buffer(t_app *app, t_thread_data *thread)
{
	int	i;

	i = -1;
	while (++i < app->overwrite_buffer_count)
	{
		if (i % THREAD_COUNT != thread->id)
			continue ;
		app->depthmap[app->overwrite_buffer[i].y][app->overwrite_buffer[i].x] = app->overwrite_buffer[i].depth;
		put_pixel_to_surface(app->surface, app->overwrite_buffer[i].x, app->overwrite_buffer[i].y, app->overwrite_buffer[i].color);
	}
}
