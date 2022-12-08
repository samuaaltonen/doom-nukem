/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linedraw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:01:44 by htahvana          #+#    #+#             */
/*   Updated: 2022/12/06 16:59:10 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	check_if_low_or_high(t_point *pixel_a, t_point *pixel_b,
										t_app *app, int color)
{
	if (abs(pixel_b->y - pixel_a->y) < abs(pixel_b->x - pixel_a->x))
	{
		if (pixel_a->x > pixel_b->x)
			linedraw_low(app, pixel_b, pixel_a, color);
		else
			linedraw_low(app, pixel_a, pixel_b, color);
	}
	else
	{
		if (pixel_a->y > pixel_b->y)
			linedraw_high(app, pixel_b, pixel_a, color);
		else
			linedraw_high(app, pixel_a, pixel_b, color);
	}
}

/**
 * @brief Draw line between two vector points
 * 
 * @param app 
 * @param a 
 * @param b 
 * @param color 
 */
void	draw_line(t_app *app, t_vector2 *a, t_vector2 *b, int color)
{
	t_point		pixel_a;
	t_point		pixel_b;

	pixel_a = world_to_screen(app, *a);
	pixel_b = world_to_screen(app, *b);
	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	check_if_low_or_high(&pixel_a, &pixel_b, app, color);
}

void	draw_point_line(t_app *app, t_point a, t_point b, int color)
{
	if (!check_borders(app, &a, &b))
		return ;
	check_if_low_or_high(&a, &b, app, color);
}

/**
 * @brief Draw line between two given wall list points
 * 
 * @param app 
 * @param a 
 * @param b 
 * @param color 
 */
void	draw_list_lines(t_app *app, t_vec2_lst *a, t_vec2_lst *b, int color)
{
	t_point		pixel_a;
	t_point		pixel_b;

	pixel_a = world_to_screen(app, a->point);
	pixel_b = world_to_screen(app, b->point);
	if (!check_borders(app, &pixel_a, &pixel_b))
		return ;
	check_if_low_or_high(&pixel_a, &pixel_b, app, color);
}
