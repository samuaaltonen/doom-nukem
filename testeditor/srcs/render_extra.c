/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/02 14:40:45 by ssulkuma         ###   ########.fr       */
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
static void	sector_bounds(t_app *app, t_sector_lst *sector,
									t_point *min, t_point *max)
{
	t_vec2_lst	*tmp;
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

static void	color_active_sector(t_app *app, t_vec2_lst *a, t_vec2_lst *b,
																int color)
{
	while (a->next != app->active_sector->wall_list
		&& b->next != app->active_sector->wall_list)
	{
		if (a->next == b)
			a = b->next;
		else if (b->next == a)
			b = a->next;
		else
			b = b->next;
		fill_triangle(app, world_to_screen(app,
				app->active_sector->wall_list->point),
			world_to_screen(app, a->point),
			world_to_screen(app, b->point), color);
	}
}

/**
 * @brief Makes triangles for rendering from a sector
 * WIP atm only renders a rectangle bounding the sector
 * 
 * @param app 
 */
void	render_fill_active_sector(t_app *app)
{
	t_vec2_lst	*a;
	t_vec2_lst	*b;
	t_point		min;
	t_point		max;
	int			color;

	color = 0x202020;
	if (interaction_sector_check(app, app->active_sector))
		color = INTERACTION;
	min = (t_point){0, 0};
	max = (t_point){0, 0};
	if (app->active_sector)
	{
		a = app->active_sector->wall_list->next;
		b = app->active_sector->wall_list->next;
		sector_bounds(app, app->active_sector, &min, &max);
		color_active_sector(app, a, b, color);
	}
}
