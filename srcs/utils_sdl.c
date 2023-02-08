/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:38:18 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/08 14:25:26 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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
	t_point	current;
	int		pixel;
	int		y;

	if (!check_blit(src, src_rect, dst, dst_rect))
		return ;
	current.y = 0;
	while (current.y < dst_rect->h && current.y + dst_rect->y < dst->h)
	{
		current.x = 0;
		y = (int)(current.y * ((float)src_rect->h / (float)dst_rect->h))
			+ src_rect->y;
		while (current.x < dst_rect->w && current.x + dst_rect->x < dst->w)
		{
			pixel = get_pixel_color(src, (int)(current.x * ((float)src_rect->w
							/ (float)dst_rect->w)) + src_rect->x, y);
			if ((pixel & 0xFF000000) > 0)
				put_pixel_to_surface(dst, current.x + dst_rect->x,
					current.y + dst_rect->y, pixel);
			current.x++;
		}
		current.y++;
	}
}

/**
 * @brief Fills al pixels in surface with color.
 * 
 * @param surface 
 * @param color 
 */
void	color_surface(SDL_Surface *surface, int color)
{
	int		x;
	int		y;
	int		pixel_pos;
	char	*pixel;

	x = 0;
	y = 0;
	while (y < surface->h)
	{
		while (x < surface->w)
		{
			pixel_pos = (y * surface->pitch)
				+ (x * IMAGE_PIXEL_BYTES);
			pixel = surface->pixels + pixel_pos;
			if ((*(int *)pixel & 0xFF000000) > 0)
				put_pixel_to_surface(surface, x, y, color);
			x++;
		}
		x = 0;
		y++;
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
		return (0);
	if (src_rect == NULL || dst_rect == NULL)
		return (0);
	return (1);
}

/**
 * @brief Sets the given rectangle parameters to the size of the given surface.
 * 
 * @param surface 
 * @param rect 
 */
void	rect_from_surface(SDL_Surface *surface, t_rect *rect)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
}
