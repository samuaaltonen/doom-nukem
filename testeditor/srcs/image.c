/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 14:37:41 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/05 13:18:40 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Changes color of a specific pixel in image.
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h
		|| x < 0 || y < 0)
		return ;
	pixel = surface->pixels + pixel_pos;
	*(int *)pixel = color;
}

/**
 * Flushes image (sets all pixels to black)
 */
void	flush_surface(SDL_Surface *surface)
{
	ft_bzero(surface->pixels, surface->h * surface->pitch);
}
