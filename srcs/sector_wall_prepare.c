/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_wall_prepare.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:46:07 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/27 17:14:25 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Translates world coordinate position to camera space and converts it to
 * window x position.
 * 
 * @param app 
 * @param coord 
 * @param dotproduct 
 * @return int 
 */
static int	translate_window_x(t_app *app, t_vector2 coord, double dotproduct)
{
	t_vector2	ray;
	double		angle;

	ray = (t_vector2){coord.x - app->player.pos.x, coord.y - app->player.pos.y};
	angle = ft_vector_angle(ray, app->player.dir);
	if (ft_line_side((t_line){app->player.pos,
			(t_vector2){app->player.pos.x + app->player.dir.x,
			app->player.pos.y + app->player.dir.y}}, coord))
		angle *= -1.0;
	if (angle < -PI_3_QUARTERS || angle > PI_3_QUARTERS)
	{
		if (dotproduct > 0.0)
			return (0);
		return (WIN_W - 1);
	}
	if (angle < -PI_HALF)
		return (0);
	else if (angle > PI_HALF)
		return (WIN_W - 1);
	else
		return ((int)(WIN_W / 2.0
			+ WIN_W * tan(angle) / app->player.camera_length / 2.0));
}

/**
 * @brief Gets wall dotproduct. Returns negative if viewing from outside (member
 * sectors).
 * 
 * @param app 
 * @param wall 
 * @return double 
 */
static double	get_wall_dotproduct(t_app *app, t_wall wall)
{
	double	dotproduct;

	dotproduct = ft_vector_dotproduct(app->player.dir, (t_vector2){
			wall.line.b.x - wall.line.a.x,
			wall.line.b.y - wall.line.a.y
		});
	if (wall.is_member && !wall.is_inside)
		return (-dotproduct);
	return (dotproduct);
}

/* static void	sector_walls_epsilon_accuracy(t_wall *walls, int wall_count)
{
	int	i;
	int	next_i;

	ft_printf("---\n");
	i = 0;
	while (i < wall_count)
	{
		next_i = i + 1;
		if (next_i == wall_count)
			next_i = 0;
		if (walls[i].is_member && walls[next_i].is_member)
			ft_printf("(%d:%d) x start: %d, x end: %d. (%d:%d) x start %d, x end: %d\n",
				walls[i].sector_id, walls[i].wall_id,
				walls[i].start_x, walls[i].end_x,
				walls[next_i].sector_id, walls[next_i].wall_id,
				walls[next_i].start_x, walls[next_i].end_x);
		i++;
	}
} */

/**
 * @brief Prepares selected walls to be rendered. Calculates their translated x
 * positions in screen.
 * 
 * @param app 
 * @param walls 
 * @param wall_count 
 */
void	sector_walls_prepare(t_app *app, t_wall *walls, int wall_count)
{
	double	dotproduct;
	int		i;
	int		temp_x;

	i = -1;
	while (++i < wall_count)
	{
		walls[i].line = get_wall_line(app,
				walls[i].sector_id,
				walls[i].wall_id);
		dotproduct = get_wall_dotproduct(app, walls[i]);
		walls[i].start_x = translate_window_x(app, walls[i].line.a, dotproduct);
		walls[i].end_x = translate_window_x(app, walls[i].line.b, dotproduct);
		if (walls[i].end_x < walls[i].start_x)
		{
			temp_x = walls[i].end_x;
			walls[i].end_x = walls[i].start_x;
			walls[i].start_x = temp_x;
			walls[i].x_flipped = TRUE;
		}
		if (walls[i].start_x < 0)
			walls[i].start_x = 0;
		if (walls[i].end_x >= WIN_W)
			walls[i].end_x = WIN_W - 1;
		walls[i].already_selected = 0;
	}
	/* sector_walls_epsilon_accuracy(walls, wall_count); */
}
