/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:59:10 by htahvana          #+#    #+#             */
/*   Updated: 2022/09/26 21:07:06 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws floor pixel.
 */
static void	floor_pixel(t_app *app, t_point *texture_coord, t_vector3 screen_pos)
{
	put_pixel_to_image_depth(app, (t_point){screen_pos.x, screen_pos.y},
		get_pixel_color(app->sprite, texture_coord->x, texture_coord->y), screen_pos.z);
	/* put_pixel_to_image_depth(app, (t_point){screen_pos.x, (abs)((int)screen_pos.y - WIN_H) - 1},
		get_pixel_color(app->sprite, texture_coord->x, texture_coord->y), screen_pos.z); */
}

/**
 * Draws horizontal scanline for the floor
 */
static void	draw_floor(t_app *app, int y, t_vector2 *step, t_vector2 *floor_pos)
{
	t_point		texture_coord;
	t_point		coord;
	int			x;
	double		distance;

	distance = 0.5f * WIN_H / (y - WIN_H / 2);
	x = -1;
	clamp_distance(&distance);
	while (++x < WIN_W)
	{
		coord = (t_point){(int)floor_pos->x, (int)floor_pos->y};
		texture_coord.x = (int)(TEX_SIZE
				* (floor_pos->x - coord.x)) & (TEX_SIZE - 1);
		texture_coord.y = (int)(TEX_SIZE
				* (floor_pos->y - coord.y)) & (TEX_SIZE - 1);
		floor_pixel(app, &texture_coord, (t_vector3){x, y, distance});
		floor_pos->x += step->x;
		floor_pos->y += step->y;
	}
}

/**
 * Casts floor from player view.
 */
static void	floor_cast(t_app *app, int y, t_vector2 *step, t_vector2 *floor_pos)
{
	t_vector2	ray_left;
	t_vector2	ray_right;
	int			ray_pos;
	double		player_height;
	double		distance;

	ray_left = (t_vector2){app->player.dir.x - app->player.cam.x,
		app->player.dir.y - app->player.cam.y};
	ray_right = (t_vector2){app->player.dir.x + app->player.cam.x,
		app->player.dir.y + app->player.cam.y};
	ray_pos = y - WIN_H * 0.5f;
	player_height = 0.5f * WIN_H;
	distance = player_height / ray_pos;
	step->x = distance * (ray_right.x - ray_left.x) / (double)WIN_W;
	step->y = distance * (ray_right.y - ray_left.y) / (double)WIN_W;
	floor_pos->x = app->player.pos.x + distance * ray_left.x;
	floor_pos->y = app->player.pos.y + distance * ray_left.y;
}

/**
 * Simply render all the ground and floor
 */
void	*render_background(void *data)
{
	t_thread_data	*t;
	t_app			*app;
	int				y;
	t_vector2		step;
	t_vector2		floor_pos;

	t = (t_thread_data *)data;
	app = (t_app *)t->app;
	y = t->id + WIN_H / 2 + 20;
	floor_pos.x = 0.f;
	floor_pos.y = 0.f;
	while (y < WIN_H)
	{
		floor_cast(app, y, &step, &floor_pos);
		draw_floor(app, y, &step, &floor_pos);
		y += THREAD_COUNT;
	}
	pthread_exit(NULL);
}
