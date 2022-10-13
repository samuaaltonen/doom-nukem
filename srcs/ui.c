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
	src.x = 0;
	src.y = 0;
	src.w = 128;
	src.h = 32;
	button = SDL_LoadBMP("assets/ui/button_iddle.bmp");
	blit_surface(button, src, app->surface, dst);
	SDL_FreeSurface(button);
}

void	blit_surface(SDL_Surface *src, t_rect src_rect,
	SDL_Surface *dst, t_rect dst_rect)
{
	int	x;
	int	y;
	int	pixel;

	if (dst_rect.w < src_rect.w || dst_rect.h < src_rect.h)
		exit_error(MSG_ERROR);
	if ((WIN_W - dst_rect.w + dst_rect.x) < 0
		|| (WIN_H - dst_rect.h + dst_rect.x) < 0)
		exit_error(MSG_ERROR);
	x = 0;
	y = 0;
	while (y < src_rect.h)
	{
		while (x < src_rect.w)
		{
			pixel = get_pixel_color(src, x + src_rect.x, y + src_rect.y);
			if ((pixel & 0xFF000000) != 0x00000000)
				put_pixel_to_surface(dst, x + dst_rect.x,
					y + dst_rect.y, pixel);
			x++;
		}
		x = 0;
		y++;
	}
}
