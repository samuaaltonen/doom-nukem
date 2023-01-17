/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:49:04 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/11 19:00:08 by saaltone         ###   ########.fr       */
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
 * @brief Shades color based on distance.
 * 
 * @param color 
 * @param shade 
 * @return int 
 */
int	shade_depth(int color, float shade)
{
	int	r;
	int	g;
	int	b;

	if (!shade)
		return (color);
	if (shade >= MAX_FOG_DISTANCE)
		return (0x000000);
	if (shade <= 0.f)
		return (0xFFFFFF);
	r = color & 0xFF0000;
	g = color & 0x00FF00;
	b = color & 0x0000FF;
	r -= (int)((r * shade) / MAX_FOG_DISTANCE);
	g -= (int)((g * shade) / MAX_FOG_DISTANCE);
	b -= (int)((b * shade) / MAX_FOG_DISTANCE);
	if (r > 0xFF0000)
		r = 0xFF0000;
	if (g > 0x00FF00)
		g = 0x00FF00;
	if (b > 0x0000FF)
		b = 0x0000FF;
	return ((r & 0xFF0000) | (g & 0x00FF00) | (b & 0x0000FF));
}

/**
 * @brief Returns pixel color at given position.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @return int 
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
