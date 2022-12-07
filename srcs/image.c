/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:34:30 by saaltone          #+#    #+#             */
/*   Updated: 2022/12/07 16:27:31 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Changes color of a specific pixel in surface.
 * 
 * @param surface 
 * @param x 
 * @param y 
 * @param color 
 */
void	put_pixel_to_surface(SDL_Surface *surface, int x, int y, int color)
{
	int		pixel_pos;
	char	*pixel;

	pixel_pos = (y * surface->pitch) + (x * IMAGE_PIXEL_BYTES);
	if (pixel_pos < 0 || x >= surface->w || y >= surface->h)
		return ;
	pixel = surface->pixels + pixel_pos;
//	if ((color & 0xFF000000) == 0xFF000000)
		*(int *)pixel = color;
	// else
	// 	*(int *)pixel = blend_pixel(int_to_argb(*(int *)pixel), int_to_argb(color));
}

int	blend_pixel(t_color base, t_color top)
{
	t_color	color;

	
	if ((top.a & 0xFF000000) > 0)
	{
		color.a = base.a + (top.a * ((255 - base.a) / 255));
		color.r = (base.r * base.a + top.r * top.a * ((255 - base.a) / 255))/color.a;
		color.g = (base.g * base.a + top.g * top.a * ((255 - base.a) / 255))/color.a;
		color.b = (base.b * base.a + top.b * top.a * ((255 - base.a) / 255))/color.a;
	}
	else
	{
		color.r = top.r;
		color.g = top.g;
		color.b = top.b;
	}
	color.a = 0xFF;
	return (argb_to_int(color));
	
}

t_color	int_to_argb(int color)
{
	t_color	argb;

	argb.a = color >> 24;
	argb.r = (color & 0x00FF0000) >> 16;
	argb.g = (color & 0x0000FF00) >> 8;
	argb.b = (color & 0x000000FF);
	return (argb);
}

int	argb_to_int(t_color color)
{
	return (color.b + (color.g << 8) + (color.r << 16) + (color.a << 24));
}