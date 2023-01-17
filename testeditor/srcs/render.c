/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/16 13:29:20 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Renders all the lines for the given sector.
 * 
 * @param app 
 * @param sector_start 
 */
void	render_sector(t_app *app, t_vec2_lst *sector_start)
{
	t_vec2_lst	*tmp;

	tmp = sector_start;
	while (tmp->next != NULL)
	{
		if (tmp->type > -1)
			draw_list_lines(app, tmp, tmp->next, PORTAL);
		else if (interaction_wall_check(app, tmp))
			draw_list_lines(app, tmp, tmp->next, INTERACTION);
		else
			draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		if (tmp->next == sector_start)
			break ;
		tmp = tmp->next;
	}
}

/**
 * @brief Runs render sector on all the sectors in app.
 * 
 * @param app
 */
void	render_sectors(t_app *app)
{
	t_sector_lst	*tmp;

	tmp = app->sectors;
	while (tmp)
	{
		render_sector(app, tmp->wall_list);
		tmp = tmp->next;
	}
}

/**
 * @brief Renders points on each corner of the active sector.
 * 
 * @param app 
 */
void	render_sector_points(t_app *app)
{
	t_vec2_lst	*head;

	if (app->active_sector)
	{
		head = app->active_sector->wall_list;
		while (head)
		{
			render_point(app, head->point, 2, POINT);
			head = head->next;
			if (head == app->active_sector->wall_list)
				break ;
		}
		if (app->wall_edit)
			change_walls_tex(app->active_sector->wall_list,
				app->active_sector->wall_list->tex);
	}
}

/**
 * @brief Renders a square with given size on the given point.
 * 
 * @param app 
 * @param point 
 * @param size 
 * @param color
 */
void	render_point(t_app *app, t_vector2 point, int size, int color)
{
	t_point		min;
	t_point		max;

	min = world_to_screen(app, point);
	max.x = min.x + size;
	max.y = min.y + size;
	min.x = min.x - size;
	min.y = min.y - size;
	while (min.y < max.y)
	{
		min.x = max.x - size * 2;
		while (min.x < max.x)
		{
			put_pixel_to_surface(app->surface, min.x, min.y, color);
			min.x++;
		}
		min.y++;
	}
}

/**
 * @brief Midpoint Circle Algorithm, calculates only one octant
 * 3 - 2 * rad avoids overdraw -rad works as well
 * 4 / 6 and 4 / 10 make the circle more circular
 * 
 * @param app
 * @param pos
 * @param rad
 * @param color
 */
void	draw_circle(t_app *app, t_point pos, int rad, int color)
{
	t_point	tmp;
	int		err;

	tmp.x = 0;
	tmp.y = rad;
	err = 3 - 2 * rad;
	while (tmp.x <= tmp.y)
	{
		put_pixel_to_surface(app->surface, pos.x + tmp.x, pos.y + tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.y, pos.y + tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.x, pos.y + tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.y, pos.y + tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.x, pos.y - tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x + tmp.y, pos.y - tmp.x, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.x, pos.y - tmp.y, color);
		put_pixel_to_surface(app->surface, pos.x - tmp.y, pos.y - tmp.x, color);
		if (err < 0)
			err += 4 * tmp.x + 6;
		else
		{
			err += 4 * (tmp.x - tmp.y) + 10;
			tmp.y--;
		}
		tmp.x++;
	}
}
