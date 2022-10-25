/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:38:18 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/21 16:10:55 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
 * Blits a source rectangle from a source surface into a destination
 * rectangle from the destination surface. Scales the source to fit
 * the destination.
 */
void	blit_surface(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect)
{
	t_point	point;
	int		pixel;
	int		x;
	int		y;

	if (check_blit(src, src_rect, dst, dst_rect) == 0)
		exit_error(MSG_ERROR);
	x = 0;
	y = 0;
	while (y < dst_rect->h)
	{
		while (x < dst_rect->w)
		{
			point.x = x;
			point.y = y;
			map_coordinates(dst_rect, src_rect, &point);
			pixel = get_pixel_color(src, point.x, point.y);
			if ((pixel & 0xFF000000) != 0x00000000)
				put_pixel_to_surface(dst, x + dst_rect->x,
					y + dst_rect->y, pixel);
			x++;
		}
		x = 0;
		y++;
	}
}
/**
 * Checks for errors before blitting the surfaces
 */
int		check_blit(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect)
{
	if (src == NULL || dst == NULL)
		return (0);
	if (src_rect == NULL || dst_rect == NULL)
		return (0);
	if (dst_rect->x + dst_rect->w > dst->w
		|| dst_rect->y + dst_rect->h > dst->h)
		return (0);
	return (1);
}

/**
 * Sets the given rectangle parameters to the size
 * of the given surface.
 */
void	rect_from_surface(SDL_Surface *surface, t_rect *rect)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
}
