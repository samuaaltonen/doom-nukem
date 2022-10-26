/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/26 09:36:54 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_ui(t_app *app)
{
	render_button(app,(t_point){10, 10}, 1);
	change_font(app, 16, 0xFFEFDCCC);
	render_text(app, (t_point){20, 20}, "FPS");
	render_text(app, (t_point){20, 20}, app->conf->fps_info);
	load_font(app);
}

t_rect	render_button(t_app *app, t_point pos, int size)
{
	t_rect		dst;
	t_rect		src;

	dst.x = pos.x;
	dst.y = pos.y;
	dst.w = app->assets.button_idle->w * size;
	dst.h = app->assets.button_idle->h * size;
	rect_from_surface(app->assets.button_idle, &src);
	if (!check_mouse(app, dst))
		blit_surface(app->assets.button_idle, &src, app->surface, &dst);
	else if (check_mouse(app, dst))
		{
			if (((SDL_GetMouseState(NULL, NULL)) & SDL_BUTTON_LMASK) != 0)
				blit_surface(app->assets.button_press, &src, app->surface, &dst);
			else
				blit_surface(app->assets.button_select, &src, app->surface, &dst);
		}
	return (dst);
}

int	check_mouse(t_app *app, t_rect rect)
{
	if (app->mouse_pos.x >= rect.x && app->mouse_pos.y >= rect.y)
	{
		if (app->mouse_pos.x <=(rect.x + rect.w)
			&& app->mouse_pos.y <=(rect.y + rect.h))
			return (1);
	}
	return (0);
}
