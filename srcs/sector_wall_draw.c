/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 12:40:36 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Reduces calculated distance based on angle to remove fisheye effect.
*/
static double	distortion_correction(t_app *app, t_vector2 ray, double distance)
{
	return (distance * cos(ft_vector_angle(ray, app->player.dir)));
}

/**
 * Translates given position to screenspace. Calculated distance and offsets.
 */
t_point_matrix	translate_to_screen_space(t_app *app, t_vector2	coord)
{
	t_vector2	ray;
	double		distance;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	distance = distortion_correction(app, ray, ft_vector_length(ray));
	/* ft_printf("Distance to coord %f %f is %f. Ray angle %f (%f deg), Distortion corrected distance %f\n",
		coord.x, coord.y, ft_vector_length(ray), 
		ft_vector_angle(app->player.dir, ray),
		ft_vector_angle(app->player.dir, ray) * RADIAN_IN_DEG,
		distance); */
	return ((t_point_matrix){
		(t_point){0, 0},
		(t_point){0, 0}
	});
}

/**
 * Draws individual sector wall, possible ceiling and floor of that vertical
 * screenline. Also updates occlusion arrays accordingly.
 */
void	sector_wall_draw(t_app *app, int sector_id, int wall_id)
{
	t_vertex2		wall_vertex;
	t_point_matrix	first_corner;
	t_point_matrix	second_corner;

	wall_vertex = get_sector_vertex_by_corner(app, sector_id, wall_id);
	first_corner = translate_to_screen_space(app, wall_vertex.a);
	second_corner = translate_to_screen_space(app, wall_vertex.b);
	// IF wall type normal wall:
	// Draw ceiling above wall
	// Draw floor below wall
	// Draw wall

	// IF portal / member
	// Draw ceiling
	// Draw floor
	// If floor higher or ceiling smaller of next sector, draw partial wall
}
