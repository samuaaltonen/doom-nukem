/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_bloom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:18:55 by htahvana          #+#    #+#             */
/*   Updated: 2022/08/08 17:58:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Renders the skybox.
 */
void	*render_skybox(void *data)
{
	t_app		*app;
	t_point		coord;
	t_vector2	steps;
	int			offset;
	double		texy;

	app = (t_app *)((t_thread_data *)data)->app;
	coord.x = ((t_thread_data *)data)->id;
	steps.y = 128 / (double)WIN_H;
	steps.x = 512 / (double)WIN_W / 2;
	while (coord.x < WIN_W)
	{
		coord.y = -1;
		texy = 0.f;
		offset = (int)((coord.x + app->conf->skybox_offset / 720.f * WIN_W * 2)
				* steps.x) % 512;
		while (++coord.y < WIN_H)
		{
			put_pixel_to_image(app->image, coord.x, coord.y,
				get_pixel_color(app->bg, offset, texy) | 0x01000000);
			texy += steps.y;
		}
		coord.x += 1;
	}
	pthread_exit(NULL);
}
