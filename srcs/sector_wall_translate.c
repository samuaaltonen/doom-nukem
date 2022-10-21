/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_translate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:46:07 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/21 16:58:05 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Translates world coordinate position to camera space and converts it to
 * window x position.
*/
static int	translate_window_x(t_app *app, t_vector2 coord, double dotproduct)
{
	t_vector2	ray;
	double		angle;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	angle = ft_vector_angle(ray, app->player.dir);
	// If left side, mark angle as negative
	if (ft_vertex_side((t_vertex2){app->player.pos,
			(t_vector2){app->player.pos.x + app->player.dir.x,
			app->player.pos.y + app->player.dir.y}}, coord))
		angle *= -1.0;
	if (angle < -PI_3_QUARTERS || angle > PI_3_QUARTERS)
	{
		if (dotproduct > 0.0)
			return (0);
		return (WIN_W - 1);
	}
	if (angle < -PI_HALF)
		return (0);
	else if (angle > PI_HALF)
		return (WIN_W - 1);
	else
		return (WIN_W / 2 + WIN_W * tan(angle) / app->player.camera_length / 2);
}

/**
 * Gets wall dotproduct. Returns negative if viewing from outside (member
 * sectors).
*/
static double	get_wall_dotproduct(t_app *app, t_wall wall)
{
	double	dotproduct;

	dotproduct = ft_vector_dotproduct(app->player.dir, (t_vector2){
			wall.vertex.b.x - wall.vertex.a.x,
			wall.vertex.b.y - wall.vertex.a.y
		});
	if (wall.is_member && !wall.is_inside)
		return (-dotproduct);
	return (dotproduct);
}

/**
 * Prepares selected walls to be rendered. Calculates their translated x
 * positions in screen.
*/
void	sector_walls_prepare(t_app *app, t_wall *walls, int wall_count)
{
	double	dotproduct;
	int		i;
	int		temp_x;

	i = -1;
	while (++i < wall_count)
	{
		walls[i].vertex = get_wall_vertex(app,
			walls[i].sector_id,
			walls[i].wall_id);
		dotproduct = get_wall_dotproduct(app, walls[i]);
		walls[i].start_x = translate_window_x(app, walls[i].vertex.a, dotproduct);
		walls[i].end_x = translate_window_x(app, walls[i].vertex.b, dotproduct);
		temp_x = walls[i].end_x;
		if (walls[i].end_x < walls[i].start_x)
		{
			walls[i].end_x = walls[i].start_x;
			walls[i].start_x = temp_x;
		}
		walls[i].start_x -= 1;
		walls[i].end_x += 1;
		if (walls[i].start_x < -1)
			walls[i].start_x = -1;
		if (walls[i].end_x >= WIN_W)
			walls[i].end_x = WIN_W - 1;
	}
}
