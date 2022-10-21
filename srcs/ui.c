/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/21 18:13:54 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_ui(t_app *app)
{
	render_button(app);

	change_font(app, 16, 0xFFEFDCCC);
	render_text(app, (t_point){20, 20}, "FPS");
	render_text(app, (t_point){20, 20}, app->conf->fps_info);
	load_font(app);
}

void	render_button(t_app *app)
{
	SDL_Surface	*button;
	t_rect		dst;
	t_rect		src;


	dst.x = 10;
	dst.y = 10;
	dst.w = 128;
	dst.h = 32;
	button = SDL_LoadBMP(BUTTON_TX);
	rect_from_surface(button, &src);
	blit_surface(button, &src, app->surface, &dst);
	SDL_FreeSurface(button);
}
