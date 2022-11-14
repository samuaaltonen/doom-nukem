/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:38:18 by dpalacio          #+#    #+#             */
/*   Updated: 2022/11/14 15:53:47 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Shades color. Shade values can be from -8 to +8. -8 is completely
 * dark (0x000000), +8 is completely white (0xFFFFFF).
 *
 * @param color 
 * @param shade 
 * @return int 
 */
int	shade_color(int color, int shade)
{
	int	r;
	int	g;
	int	b;

	if (!shade)
		return (color);
	if (shade <= -8)
		return (0x000000);
	if (shade >= 8)
		return (0xFFFFFF);
	r = color & 0xFF0000;
	g = color & 0x00FF00;
	b = color & 0x0000FF;
	r += (r * shade) >> 3;
	g += (g * shade) >> 3;
	b += (b * shade) >> 3;
	if (r > 0xFF0000)
		r = 0xFF0000;
	if (g > 0x00FF00)
		g = 0x00FF00;
	if (b > 0x0000FF)
		b = 0x0000FF;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
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
 * Blits a source rectangle from a source surface into a destination
 * rectangle from the destination surface. Scales the source to fit
 * the destination.
 */
void	blit_surface(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect)
{
	t_point	point;
	t_point	current;
	int		pixel;

	if (check_blit(src, src_rect, dst, dst_rect))
	{
		current.x = 0;
		current.y = 0;
		while (current.y < dst_rect->h)
		{
			while (current.x < dst_rect->w)
			{
				point.x = current.x;
				point.y = current.y;
				map_coordinates(dst_rect, src_rect, &point);
				pixel = get_pixel_color(src, point.x, point.y);
				if ((pixel & 0xFF000000) != 0x00000000)
					put_pixel_to_surface(dst, current.x + dst_rect->x,
						current.y + dst_rect->y, pixel);
				current.x++;
			}
			current.x = 0;
			current.y++;
		}
	}
}

/**
 * Checks for errors before blitting the surfaces
 */
int	check_blit(SDL_Surface *src, t_rect *src_rect,
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
