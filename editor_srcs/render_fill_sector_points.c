/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fill_sector_points.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:55:36 by htahvana          #+#    #+#             */
/*   Updated: 2023/02/01 17:13:30 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns window boundary line based on side id.
 * 
 * @param app 
 * @param side_id 
 * @return t_line 
 */
static t_line	get_window_line(t_app *app, int side_id)
{
	if (side_id == 0)
		return ((t_line){app->view_start,
			ft_vector2_add(app->view_start, (t_vector2){app->view_size.x, 0})});
	if (side_id == 1)
		return ((t_line){ft_vector2_add(app->view_start,
				(t_vector2){app->view_size.x, 0}),
					ft_vector2_add(app->view_start,
				(t_vector2){app->view_size.x, app->view_size.y})});
	if (side_id == 2)
		return ((t_line){ft_vector2_add(app->view_start, (t_vector2){
				app->view_size.x, app->view_size.y}), ft_vector2_add(
				app->view_start, (t_vector2){0, app->view_size.y})});
	return ((t_line){ft_vector2_add(app->view_start,
			(t_vector2){0, app->view_size.y}), app->view_start,});
}

/**
 * @brief Checks if point is on the screen.
 * 
 * @param app 
 * @param point 
 * @return t_bool 
 */
static t_bool	point_on_screen(t_app *app, t_vector2 point)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (ft_line_side(get_window_line(app, i), point))
			return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Adds point to the point array.
 * 
 * @param point 
 * @param array 
 * @param count 
 */
static void	add_point(t_vector2 point, t_vector2 *array, int *count)
{
	array[*count] = point;
	(*count)++;
}

/**
 * @brief Adds window boundary points when they are inside the sector.
 * 
 * @param app 
 * @param array 
 * @param sector 
 * @param count 
 */
static void	add_window_boundary_points(t_app *app, t_vector2 *array,
	t_sector_lst *sector, int *count)
{
	t_line		line;
	int			i;

	i = -1;
	while (++i < 4)
	{
		line = get_window_line(app, i);
		if (inside_sector_check(sector, &(line.a)))
			add_point(line.a, array, count);
	}
}

/**
 * @brief Builds point array of the sector for filling.
 * 
 * @param app 
 * @param array 
 * @param sector 
 * @param count 
 */
void	make_point_array(t_app *app, t_vector2 *array, t_sector_lst *sector,
																	int *count)
{
	int			i;
	t_line		wall_line;
	t_vec2_lst	*tmp;
	t_vector2	point;

	tmp = sector->wall_list;
	while (tmp)
	{
		wall_line = (t_line){tmp->point, tmp->next->point};
		i = -1;
		while (++i < 4)
		{
			if (ft_line_intersection_segment(get_window_line(app, i),
					wall_line, &point))
				add_point(ft_vector2_add(point,
						(t_vector2){i * 0.001f, i * 0.001f}), array, count);
		}
		if (point_on_screen(app, tmp->point))
			add_point(tmp->point, array, count);
		tmp = tmp->next;
		if (tmp == sector->wall_list)
			break ;
	}
	add_window_boundary_points(app, array, sector, count);
	sort_point_array(array, count);
}
