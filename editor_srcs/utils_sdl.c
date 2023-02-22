/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:38:18 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/21 13:41:20 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * @brief Returns pixel color at given position.
 * 
 * @param surface
 * @param x
 * @param y
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
 * @brief Gets map coordinates.
 * 
 * @param src
 * @param dst
 * @param point
*/
static void	map_coordinates(t_rect *src, t_rect *dst, t_point *point)
{
	point->x = point->x * ((float)dst->w / (float)src->w) + dst->x;
	point->y = point->y * ((float)dst->h / (float)src->h) + dst->y;
}

/**
 * @brief Blits a source rectangle from a source surface into a destination
 * rectangle from the destination surface. Scales the source to fit
 * the destination.
 * 
 * @param src
 * @param src_rect
 * @param dst
 * @param dst_rect
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
 * @brief Checks for errors before blitting the surfaces.
 * 
 * @param src
 * @param src_rect
 * @param dst
 * @param dst_rect
 * @return int
 */
int	check_blit(SDL_Surface *src, t_rect *src_rect,
	SDL_Surface *dst, t_rect *dst_rect)
{
	if (src == NULL || dst == NULL)
		return (FALSE);
	if (src_rect == NULL || dst_rect == NULL)
		return (FALSE);
	if (dst_rect->x + dst_rect->w > dst->w
		|| dst_rect->y + dst_rect->h > dst->h)
		return (FALSE);
	return (TRUE);
}
