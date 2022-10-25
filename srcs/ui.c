/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/25 12:08:48 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_ui(t_app *app)
{
	render_button(app,(t_point){10, 10}, 0, 1);

	change_font(app, 16, 0xFFEFDCCC);
	render_text(app, (t_point){20, 20}, "FPS");
	render_text(app, (t_point){20, 20}, app->conf->fps_info);
	load_font(app);
}

t_rect	render_button(t_app *app, t_point pos, int state, int size)
{
	t_rect		dst;
	t_rect		src;

	state = 0;
	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = app->assets.button_texture->w * size;
	dst.h = app->assets.button_texture->h * size;
	rect_from_surface(app->assets.button_texture, &src);
	blit_surface(app->assets.button_texture, &src, app->surface, &dst);
	return (dst);
}
