/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:51 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 17:15:49 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Draws vertical line.
 */
static void	draw_vertical(t_app *app, int sector_id, int wall_id,
	t_point_matrix screen)
{
	int		start;

	(void)sector_id;
	(void)wall_id;
	start = screen.a.y;
	while (start < screen.b.y)
	{
		put_pixel_to_surface(app->surface, screen.a.x, start, 0xFFFFFF);
		start++;
	}
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
	first_corner = translate_to_screen_space(app, sector_id, wall_vertex.a);
	second_corner = translate_to_screen_space(app, sector_id, wall_vertex.b);
	/* ft_printf("Wall %d of sector %d screen pixels are (%4d %4d to %4d %4d) and (%4d %4d to %4d %4d)\n",
		wall_id, sector_id,
		first_corner.a.x, first_corner.a.y, first_corner.b.x, first_corner.b.y,
		second_corner.a.x, second_corner.a.y, second_corner.b.x, second_corner.b.y); */
	// IF wall type normal wall:
	// Draw ceiling above wall
	// Draw floor below wall
	// Draw wall
	draw_vertical(app, sector_id, wall_id, first_corner);
	draw_vertical(app, sector_id, wall_id, second_corner);

	// IF portal / member
	// Draw ceiling
	// Draw floor
	// If floor higher or ceiling smaller of next sector, draw partial wall
}
