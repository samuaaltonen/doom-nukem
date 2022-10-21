/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:18:36 by htahvana          #+#    #+#             */
/*   Updated: 2022/10/21 13:43:29 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief renders all the lines for the given sector
 * 
 * @param app 
 * @param sector_start 
 */
void	render_sector(t_app *app, t_vec2_lst *sector_start)
{
	t_vec2_lst *tmp;

	tmp = sector_start;
	while (tmp->next != NULL)
	{
		if(tmp->wall_type > -1)
			draw_list_lines(app, tmp, tmp->next, PORTAL);
		else
			draw_list_lines(app, tmp, tmp->next, 0xEEEEEE);
		if (tmp->next == sector_start)
			break ;
		tmp = tmp->next;
	}
}

/**
 * @brief runs render sector on all the sectors in app
 * 
 * @param app 
 */
void	render_sectors(t_app *app)
{
	t_sector_lst *tmp;

	tmp = app->sectors;
	while(tmp)
	{
		render_sector(app, tmp->wall_list);
		tmp = tmp->next;
	}
}

static void	render_row(t_app *app, int y, int color)
{
	int	x;

	x = -1;
	while (++x < app->surface->w)
		put_pixel_to_surface(app->surface, x, y, color);
}

static void	render_col(t_app *app, int x, int color)
{
	int	y;

	y = -1;
	while (++y < app->surface->h)
		put_pixel_to_surface(app->surface, x, y, color);
}

/**
 * @brief renders a grid with the divider and color param
 * 
 * @param app 
 * @param divider 
 * @param color 
 */
void	render_grid(t_app *app, double divider, int color)
{
	int			x;
	int			y;
	t_vector2	screen;
	t_vector2	prev;

	y = 0;
	x = 0;
	prev = (t_vector2){0.0f,0.0f};
	while (y < app->surface->h)
 	{
		screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
		screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;
		if(fmod(screen.y, divider) > prev.y || screen.y == 0.0f)
			render_row(app, y, color);
		prev.y = fmod(screen.y, divider);
		y++;
	}
	while (x < app->surface->w)
	{
		screen.x = app->view_pos.x + (x / (double)app->surface->w) * app->zoom_area.x;
		screen.y = app->view_pos.y + (y / (double)app->surface->h) * app->zoom_area.y;
		if(fmod(screen.x, divider) < prev.x || screen.x == 0.0f)
			render_col(app, x, color);
		prev.x = fmod(screen.x, divider);

		x++;
	}
		//-50 + ( 0  / 1000) * 100
}

/**
 * @brief Puts the max and min values of a bounding box of a sector to the given min and max param
 * 
 * @param app 
 * @param sector 
 * @param min 
 * @param max 
 */
static void	sector_bounds(t_app *app, t_sector_lst *sector, t_point *min, t_point *max)
{
	t_vec2_lst *tmp;
	t_point screen;

	tmp = sector->wall_list;
	min->x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
	min->y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
	max->x = min->x;
	max->y = min->y;
	while(tmp)
	{
		screen.x = (tmp->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
		screen.y = (tmp->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
		if(screen.x < min->x)
			min->x = screen.x;
		if(screen.x > max->x)
			max->x = screen.x;
		if(screen.y < min->y)
			min->y = screen.y;
		if(screen.y > max->y)
			max->y = screen.y;
		tmp = tmp->next;
		if(tmp == sector->wall_list)
			break;
	}
}

/**
 * @brief renders points on each point of the active sector
 * 
 * @param app 
 */
void	render_sector_points(t_app *app)
{
	t_vec2_lst *head;

	if(app->active_sector)
	{
		head = app->active_sector->wall_list;
		while(head)
		{
			render_selection_point(app, head, 2);
			head = head->next;
			if(head == app->active_sector->wall_list)
				break;
		}
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
	t_vec2_lst *a;
	t_vec2_lst *b;
	t_point min;
	t_point max;
	t_point cur;

	min = (t_point){0,0};
	max = (t_point){0,0};

	if(app->active_sector)
	{
		a = app->active_sector->wall_list->next;
		b = app->active_sector->wall_list->next;
		sector_bounds(app,app->active_sector, &min, &max);
		while(a->next != app->active_sector->wall_list && b->next != app->active_sector->wall_list)
		{
			if(a->next == b)
				a = b->next;
			else if(b->next == a)
				b = a->next;
			else
				b = b->next;
			//draw triangle start-a-b
		}
		//wip draw square instead
		cur = (t_point){min.x, min.y};
		while(cur.y < max.y)
		{
			cur.x = min.x;
			while(cur.x < max.x)
			{
				put_pixel_to_surface(app->surface, cur.x, cur.y, 0x202020);
				cur.x++;
			}
			cur.y++;
		}
	}
}

/**
 * @brief Renders a square with given size on the given point
 * 
 * @param app 
 * @param point 
 * @param size 
 */
void	render_selection_point(t_app *app, t_vec2_lst *point, int size)
{
	t_point min;
	t_point max;

	if(point)
	{
		min.x = (point->point.x - app->view_pos.x) * (app->surface->w) / (app->view_size.x - app->view_pos.x);
		min.y = (point->point.y - app->view_pos.y) * (app->surface->h) / (app->view_size.y - app->view_pos.y);
		max.x = min.x + size;
		max.y = min.y + size;
		min.x = min.x - size;
		min.y = min.y - size;
		while(min.y < max.y)
		{
			min.x = max.x - size * 2;
			while(min.x < max.x)
				{
					put_pixel_to_surface(app->surface, min.x, min.y, 0xFF00FF);
					min.x++;
				}
			min.y++;
		}
	}
}