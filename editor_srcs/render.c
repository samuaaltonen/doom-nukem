/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/27 17:07:54 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	sort_line_points(t_line *line)
{
	if (line->a.y < line->b.y)
		ft_vec2_swap(&line->a, &line->b);
	else if (line->a.y == line->b.y && line->a.x > line->b.x)
		ft_vec2_swap(&line->a, &line->b);
	return ;
}

static t_bool	same_line_points(t_line a, t_line b)
{
	sort_line_points(&a);
	sort_line_points(&b);
	if(a.a.x == b.a.x
		&& a.a.y == b.a.y
		&& a.b.x == b.b.x
		&& a.b.y == b.b.y)
		return (TRUE);
	return (FALSE);
}

int	find_wall_match(t_app *app, t_vec2_lst *wall, t_sector_lst *start)
{
	int	i;
	t_sector_lst	*target_sector;
	t_vec2_lst		*target_wall;

	target_sector = sector_by_index(app, wall->type);
	i = -1;
	target_wall = target_sector->wall_list;
	while (++i < target_sector->corner_count + 1)
	{
		if(same_line_points((t_line){wall->point, wall->next->point},
				(t_line){target_wall->point, target_wall->next->point}) && target_wall->type == get_sector_id(app, start))
			return (TRUE);
		target_wall = target_wall->next;
	}
	return (FALSE);
}

/**
 * @brief Renders all the lines for the given sector.
 * 
 * @param app 
 * @param sector_start 
 */
void	render_sector(t_app *app, t_vec2_lst *wall_start, t_sector_lst *sector)
{
	t_vec2_lst	*tmp;

	tmp = wall_start;
	while (tmp->next != NULL)
	{
		if (tmp->type > -1)
		{
			if(find_wall_match(app, tmp, sector))
				draw_list_lines(app, tmp, tmp->next, PORTAL_LINK);
			else
				draw_list_lines(app, tmp, tmp->next, PORTAL);
		}
		else
			draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		if (interaction_wall_check(app, tmp))
			render_decor(app, tmp, INTERACTION);
		else
			render_decor(app, tmp, 0xEEEEEE);
		if (tmp->next == wall_start)
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
		render_sector(app, tmp->wall_list, tmp);
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
