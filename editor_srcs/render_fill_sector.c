/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fill_sector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/16 15:04:51 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Puts the max and min values of a bounding box of a sector to the
 * given min and max param.
 * 
 * @param app 
 * @param sector 
 * @param min 
 * @param max 
 */
static void	sector_bounds(t_app *app, t_sector_list *sector,
									t_point *min, t_point *max)
{
	t_wall_list	*tmp;
	t_point		screen;

	tmp = sector->wall_list;
	*min = world_to_screen(app, tmp->point);
	max->x = min->x;
	max->y = min->y;
	while (tmp)
	{
		screen = world_to_screen(app, tmp->point);
		if (screen.x < min->x)
			min->x = screen.x;
		if (screen.x > max->x)
			max->x = screen.x;
		if (screen.y < min->y)
			min->y = screen.y;
		if (screen.y > max->y)
			max->y = screen.y;
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
}

/**
 * @brief Fills sector with color.
 * 
 * @param app 
 * @param sector 
 * @param color 
 */
static void	color_sector(t_app *app, t_sector_list *sector, int color)
{
	t_vector2	render_points[MAX_SECTOR_CORNERS + 4];
	int			point_count;
	int			i;

	point_count = 0;
	make_point_array(app, (t_vector2 *)&render_points, sector, &point_count);
	i = -1;
	while (++i < point_count - 1)
	{
		fill_triangle(app, (t_triangle){world_to_screen(app,
				render_points[0]), world_to_screen(app, render_points[i]),
			world_to_screen(app, render_points[i + 1])}, color);
	}
}

/**
 * @brief Makes triangles for rendering from a sector
 * 
 * @param app 
 */
void	render_fill_sector(t_app *app, t_sector_list *sector, int color)
{
	t_point		min;
	t_point		max;

	if (sector == NULL)
		return ;
	if (interaction_sector_check(app, sector) && color == GREY)
		color = INTERACTION;
	min = (t_point){0, 0};
	max = (t_point){0, 0};
	sector_bounds(app, sector, &min, &max);
	color_sector(app, sector, color);
}
