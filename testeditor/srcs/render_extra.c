/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/09 18:03:39 by htahvana         ###   ########.fr       */
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


static t_line	get_window_line(t_app *app, int side_id)
{
	if (side_id == 0)
		return ((t_line){app->view_pos,
		ft_vector2_add(app->view_pos,(t_vector2){app->zoom_area.x, 0})});
	if (side_id == 1)
		return ((t_line){ft_vector2_add(app->view_pos,
				(t_vector2){app->zoom_area.x, 0}),ft_vector2_add(app->view_pos,
				(t_vector2){app->zoom_area.x, app->zoom_area.y})});
	if (side_id == 2)
		return ((t_line){ft_vector2_add(app->view_pos, (t_vector2){
				app->zoom_area.x, app->zoom_area.y}), ft_vector2_add(
				app->view_pos,(t_vector2){0, app->zoom_area.y})});
	return ((t_line){ft_vector2_add(app->view_pos,
			(t_vector2){0,app->zoom_area.y}),app->view_pos,});
}

static void	sort_point_array(t_vector2 *array, int *count)
{
	double		angles[MAX_SECTOR_CORNERS + 4];
	int			i;
	int			k;

	i = -1;
	while (++i < *count)
	{
		if(array[i].y < array[0].y || (array[i].y == array[0].y && array[i].x >= array[0].x))
			ft_vec2_swap(&(array[0]), &(array[i]));
	}
	i = 0;
	angles[0] = 0.f;
	while (++i < *count)
		angles[i] = ft_vector_angle((t_vector2){-1.f,0.f},ft_vector2_sub(array[i],array[0]));
	i = -1;
	while (++i < *count - 1)
	{
		k = -1;
		while (++k < *count - i - 1)
		{
			if(angles[k] > angles[k + 1])
			{
				ft_double_swap(&(angles[k]), &(angles[k + 1]));
				ft_vec2_swap(&(array[k]), &(array[k + 1]));
			}
			else if(angles[k] == 0.f && angles[k] == angles[k + 1] && array[k].x < array[k + 1].x)
				ft_vec2_swap(&(array[k]), &(array[k + 1]));
		}	
	}
}


static t_bool	point_on_screen(t_app *app, t_vector2 point)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if(ft_line_side(get_window_line(app,i), point))
			return (FALSE);
	}
	return (TRUE);
}

static void	add_point(t_vector2 point, t_vector2 *array, int *count)
{
	array[*count] = point;
	(*count)++;
}

 void	make_point_array(t_app *app, t_vector2 *array, t_sector_lst *sector, int *count)
{
	int i;

	t_line		wall_line;
	t_vec2_lst	*tmp;
	t_vector2	point;
	t_line		line;

	tmp = sector->wall_list;
	while(tmp)
	{
		wall_line.a = tmp->point;
		wall_line.b = tmp->next->point;
		i = -1;
		while(++i < 4)
		{
			line = get_window_line(app, i);
			if(ft_line_intersection_segment(line ,wall_line, &point))
				add_point(ft_vector2_add(point,(t_vector2){i * 0.001f, i * 0.001f}), array, count);
		}
		if(point_on_screen(app, tmp->point))
			add_point(tmp->point, array, count);
		tmp = tmp->next;
		if(tmp == sector->wall_list)
			break;
	}
	i = -1;
	while (++i < 4)
	{
		line = get_window_line(app, i);
		if(inside_sector_check(sector, &(line.a)))
			add_point(line.a, array, count);
	}
	sort_point_array(array, count);
}

static void	color_sector(t_app *app, t_sector_lst *sector, int color)
{
	t_vector2	render_points[MAX_SECTOR_CORNERS + 4];
	int			point_count;
	int			i;

	point_count = 0;
	make_point_array(app, (t_vector2 *)&render_points,sector,&point_count);
	i = -1;
	while (++i < point_count - 1)
	{
		fill_triangle(app, world_to_screen(app,
				render_points[0]),
			world_to_screen(app, render_points[i]),
			world_to_screen(app, render_points[i + 1]), color);
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
		sector_bounds(app, app->active_sector, &min, &max);
		color_sector(app,app->active_sector, color);
	}
}
