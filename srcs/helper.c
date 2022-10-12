/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:32:04 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/11 16:46:48 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Reduces calculated distance based on angle to remove fisheye effect.
*/
double	distortion_correction(double angle, double distance)
{
	return (distance * cos(angle));
}

/**
 * Clamps distance to maximum distance.
 */
void	clamp_distance(double *distance)
{
	if (*distance > MAX_RAY_DISTANCE)
		*distance = MAX_RAY_DISTANCE;
}

/**
 * Returns radial direction of a vector.
 */
double	get_radial_direction(t_vector2 *vector)
{
	double	rad;

	rad = atan2(vector->x, vector->y);
	if (rad < 0)
		rad = rad + 2 * M_PI;
	rad = rad * (180 / M_PI);
	return (rad);
}

/**
 * Returns pixel color at given position.
 */
int	get_pixel_color(SDL_Surface *surface, int x, int y)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return (0);
	pixel = surface->pixels + pixel_pos;
	return (*(int *)pixel);
}

/**
 * Flushes image (sets all pixels to black)
 */
void	flush_surface(SDL_Surface *surface)
{
	ft_bzero(surface->pixels, surface->h * surface->pitch);
}

/**
 * Updates the info string with given value backwards from given index
 */
static void	update_value(t_app *app, int value, int char_index)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		app->conf->fps_info[char_index - i] = value % 10 + '0';
		value = value / 10;
	}
}

/**
 * Updates all the values.
 */
void	update_info(t_app *app)
{
	update_value(app, app->conf->fps, 7);
}
