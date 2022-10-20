/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/20 12:06:57 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	title_screen(t_app *app)
{
	SDL_Surface	*bg;
	t_rect		dst;
	t_rect		src;

	bg = SDL_LoadBMP("assets/ui/menu-bg.bmp");
	rect_from_surface(bg, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(bg, &src, app->surface, &dst);
	SDL_FreeSurface(bg);
	render_menu(app);
}
