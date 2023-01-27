/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/27 15:38:40 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Changes color of a specific pixel in surface.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return ;
	pixel = surface->pixels + pixel_pos;
//	if ((color & 0xFF000000) == 0xFF000000)
		*(int *)pixel = color;
	/* else
	 	*(int *)pixel = blend_pixel(int_to_argb(*(int *)pixel), int_to_argb(color));
	*/
}

/* int	blend_pixel(t_colors base, t_colors top)
{
	t_colors	color;

	if ((top.a & 0xFF000000) > 0)
	{
		color.a = base.a + (top.a * ((255 - base.a) / 255));
		color.r = (base.r * base.a + top.r * top.a * ((255 - base.a) / 255))
			/ color.a;
		color.g = (base.g * base.a + top.g * top.a * ((255 - base.a) / 255))
			/ color.a;
		color.b = (base.b * base.a + top.b * top.a * ((255 - base.a) / 255))
			/ color.a;
	}
	else
	{
		color.r = top.r;
		color.g = top.g;
		color.b = top.b;
	}
	color.a = 0xFF;
	return (color.color);
} */

/**
 * @brief Changes color of a specific pixel in surface.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_to_surface_check(t_app *app, t_point point,
	int color, float distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->surface->pitch) + (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x >= app->surface->w
		|| point.y >= app->surface->h)
		return ;
	if (app->depthmap[point.y / 2][point.x] >= distance)
	{
		pixel = app->surface->pixels + pixel_pos;
		if (point.y % 2)
			app->depthmap[point.y / 2][point.x] = distance;
		*(int *)pixel = color;
	}
}
