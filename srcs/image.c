/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/19 13:20:01 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Initializes image.
 */
SDL_Surface	*init_image(int width, int height)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 
		IMAGE_PIXEL_BITS, SDL_PIXELFORMAT_ARGB8888);
	if (!surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	return (surface);
}

/**
 * Initializes XPM image.
 */
SDL_Surface	*load_texture(char *path)
{
	SDL_Surface	*surface;
	SDL_Surface	*argb_converted;
	SDL_RWops	*rwops;
	int			clear_alpha;

	rwops = SDL_RWFromFile(path, "rb");
	if (!rwops)
		exit_error(MSG_ERROR_IMAGE_INIT);
	surface = SDL_LoadBMP_RW(rwops, SDL_TRUE);
	if (!surface
		&& SDL_RWclose(rwops) < 0)
		exit_error(MSG_ERROR_IMAGE_INIT);
	argb_converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
	if (!argb_converted)
		exit_error(MSG_ERROR_IMAGE_INIT);
	SDL_FreeSurface(surface);
	surface = argb_converted;
	SDL_LockSurface(surface);
	clear_alpha = 0;
	while (clear_alpha < surface->w * surface->h)
	{
		*((unsigned int *)surface->pixels + clear_alpha) &= 0x00FFFFFF;
		clear_alpha++;
	}
	return (surface);
}

/**
 * Changes color of a specific pixel in image.
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
 * Puts pixel to image and depthmap
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
