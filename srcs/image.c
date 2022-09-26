/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/09/26 21:10:54 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * Initializes image.
 */
t_image	*init_image(int width, int height)
{
	t_image	*image;

	image = (t_image *)malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->width = width;
	image->height = height;
	image->surface = SDL_CreateRGBSurfaceWithFormat(0, image->width, image->height, 
		IMAGE_PIXEL_BITS, SDL_PIXELFORMAT_ARGB8888);
	if (!image->surface)
		exit_error(MSG_ERROR_IMAGE_INIT);
	image->data = image->surface->pixels;
	image->line_size = image->surface->pitch;
	return (image);
}

/**
 * Initializes XPM image.
 */
t_image	*init_xpm_image(char *path)
{
	SDL_Surface	*argb_converted;
	SDL_RWops	*rwops;
	t_image		*image;
	int			clear_alpha;

	image = (t_image *)malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	rwops = SDL_RWFromFile(path, "rb");
	if (!rwops)
		exit_error(MSG_ERROR_IMAGE_INIT);
	image->surface = IMG_LoadXPM_RW(rwops);
	if (!image->surface
		&& SDL_RWclose(rwops) < 0)
		exit_error(MSG_ERROR_IMAGE_INIT);
	argb_converted = SDL_ConvertSurfaceFormat(image->surface, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(image->surface);
	image->surface = argb_converted;
	SDL_LockSurface(image->surface);
	image->line_size = image->surface->pitch;
	image->width = image->surface->w;
	image->height = image->surface->h;
	image->data = image->surface->pixels;
	clear_alpha = 0;
	while (clear_alpha < image->width * image->height)
	{
		*((unsigned int *)image->data + clear_alpha) &= 0x00FFFFFF;
		clear_alpha++;
	}
	//ft_printf("Image %-40s dimension: %8d x %8d line size %8d\n", path, image->width, image->height, image->line_size);
	return (image);
}

/**
 * Changes color of a specific pixel in image.
 */
void	put_pixel_to_image(t_image *image, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * image->line_size) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= image->width || y >= image->height)
		return ;
	pixel = image->data + pixel_pos;
	*(int *)pixel = color;
}

/**
 * Puts pixel to image and depthmap
 */
void	put_pixel_to_image_depth(t_app *app, t_point point, int color,
	double distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->image->line_size)
		+ (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x >= app->image->width
		|| point.y >= app->image->height)
		return ;
	pixel = app->image->data + pixel_pos;
	app->depthmap[point.y][point.x] = distance;
	if (color > 0)
		*(int *)pixel = color;
}

/**
 * Tests if there is something over the pixel from depthmap before putting it.
 */
void	put_pixel_to_image_check(t_app *app, t_point point, int color,
	double distance)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (point.y * app->image->line_size)
		+ (point.x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || point.x >= app->image->width
		|| point.y >= app->image->height)
		return ;
	pixel = app->image->data + pixel_pos;
	if (app->depthmap[point.y][point.x] < distance &&
		app->depthmap[point.y][point.x] != 0.f)
		return ;
	app->depthmap[point.y][point.x] = distance;
	if (color > 0)
		*(unsigned int *)pixel = color;
}
