/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/10/26 16:42:14 by saaltone         ###   ########.fr       */
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
