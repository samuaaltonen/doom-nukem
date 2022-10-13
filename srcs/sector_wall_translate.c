/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_translate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:46:07 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/13 23:18:45 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Translates world coordinate position to camera space and converts it to
 * window x position.
*/
int	translate_window_x(t_app *app, t_vector2 coord)
{
	int			x;
	t_vector2	ray;
	double		angle;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	angle = ft_vector_angle(ray, app->player.dir);
	// If left side, mark angle as negative
	if (ft_vertex_side((t_vertex2){app->player.pos,
			(t_vector2){app->player.pos.x + app->player.dir.x,
			app->player.pos.y + app->player.dir.y}}, coord))
		angle *= -1.0;
	if (angle < -M_2_PI)
		x = 0;
	else if (angle > M_2_PI)
		x = WIN_W - 1;
	else
		x = WIN_W / 2 + WIN_W * tan(angle) / app->player.camera_length / 2;
	return (x);
}

void	prepare_sector_walls(t_app *app)
{
	int	i;
	int	temp_x;

	i = -1;
	while (++i < app->possible_visible_count)
	{
		app->possible_visible[i].vertex = get_sector_vertex_by_corner(app,
			app->possible_visible[i].sector_id,
			app->possible_visible[i].wall_id);
		app->possible_visible[i].start_x = translate_window_x(app, app->possible_visible[i].vertex.a);
		app->possible_visible[i].end_x = translate_window_x(app, app->possible_visible[i].vertex.b);
		temp_x = app->possible_visible[i].end_x;
		if (app->possible_visible[i].end_x < app->possible_visible[i].start_x)
		{
			app->possible_visible[i].end_x = app->possible_visible[i].start_x;
			app->possible_visible[i].start_x = temp_x;
		}
		app->possible_visible[i].start_x -= 2;
		app->possible_visible[i].end_x += 2;
		if (app->possible_visible[i].start_x < -1)
			app->possible_visible[i].start_x = -1;
		if (app->possible_visible[i].end_x >= WIN_W)
			app->possible_visible[i].end_x = WIN_W - 1;
	}
}
