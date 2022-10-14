/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/14 16:09:47 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

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

void	render_menu(t_app *app)
{
	SDL_Surface	*button;
	t_rect		dst;
	t_rect		src;


	dst.x = 640 - 256;
	dst.y = 64;
	dst.w = 512;
	dst.h = 128;
	button = SDL_LoadBMP("assets/ui/button_iddle.bmp");
	rect_from_surface(button, &src);
	blit_surface(button, &src, app->surface, &dst);
	SDL_FreeSurface(button);
}