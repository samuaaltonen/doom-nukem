/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/20 16:00:49 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Creates a srface with the specified width and height.
 *
SDL_Surface	*create_surface(int width, int height)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 
		IMAGE_PIXEL_BITS, SDL_PIXELFORMAT_ARGB8888);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	return (surface);
}*/

/**
 * Changes color of a specific pixel in surface.
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return ;
	pixel = surface->pixels + pixel_pos;
	*(int *)pixel = color;
}

/**
 * Puts pixel to surface and depthmap
 */
void	put_pixel_to_surface_depth(t_app *app, t_point point, int color,
	double distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->surface->pitch)
		+ (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x >= app->surface->w
		|| point.y >= app->surface->h)
		return ;
	pixel = app->surface->pixels + pixel_pos;
	app->depthmap[point.y][point.x] = distance;
	if (color > 0)
		*(int *)pixel = color | 0xFF000000;
}

/**
 * Tests if there is something over the pixel from depthmap before putting it.
 */
void	put_pixel_to_surface_check(t_app *app, t_point point, int color,
	double distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->surface->pitch)
		+ (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x >= app->surface->w
		|| point.y >= app->surface->h)
		return ;
	pixel = app->surface->pixels + pixel_pos;
	if (app->depthmap[point.y][point.x] < distance &&
		app->depthmap[point.y][point.x] != 0.f)
		return ;
	app->depthmap[point.y][point.x] = distance;
	if (color > 0)
		*(unsigned int *)pixel = color | 0xFF000000;
}
