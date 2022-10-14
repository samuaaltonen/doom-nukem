/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/13 14:19:15 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

Uint32	get_pixel(SDL_Surface *surface, int x, int y);
void	set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void	render_button(t_app *app)
{
	SDL_Surface	*button;
	t_rect		dst;
	t_rect		src;


	dst.x = 10;
	dst.y = 10;
	dst.w = 128;
	dst.h = 32;
	button = SDL_LoadBMP("assets/ui/button_iddle.bmp");
	rect_from_surface(button, &src);
	blit_surface(button, &src, app->surface, &dst);
	SDL_FreeSurface(button);
}

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
			map_point(dst_rect, src_rect, &point);
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

void	rect_from_surface(SDL_Surface *surface, t_rect *rect)
{
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
}

void	map_point(t_rect *src, t_rect *dst, t_point *point)
{
	point->x = point->x * ((float)dst->w / (float)src->w) + dst->x;
	point->y = point->y * ((float)dst->h / (float)src->h) + dst->y;
}