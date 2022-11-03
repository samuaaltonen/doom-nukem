/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/11/03 14:35:10 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Puts the max and min values of a bounding box of a sector to the given min and max param
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
	min->x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	min->y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
	max->x = min->x;
	max->y = min->y;
	while (tmp)
	{
		screen.x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
		screen.y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
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
	t_point		cur;

	min = (t_point){0, 0};
	max = (t_point){0, 0};
	if (app->active_sector)
	{
		a = app->active_sector->wall_list->next;
		b = app->active_sector->wall_list->next;
		sector_bounds(app, app->active_sector, &min, &max);
		while (a->next != app->active_sector->wall_list && b->next != app->active_sector->wall_list)
		{
			if (a->next == b)
				a = b->next;
			else if (b->next == a)
				b = a->next;
			else
				b = b->next;
			//draw triangle start-a-b
		}
		//wip draw square instead
		cur = (t_point){min.x, min.y};
		while (cur.y < max.y)
		{
			cur.x = min.x;
			while (cur.x < max.x)
			{
				put_pixel_to_surface(app->surface, cur.x, cur.y, 0x202020);
				cur.x++;
			}
			cur.y++;
		}
	}
}
