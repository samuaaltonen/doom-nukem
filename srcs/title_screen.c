/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/21 16:46:52 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	title_screen(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	render_menu(app);
}

void	render_menu(t_app *app)
{
	//t_rect		dst;
	//t_rect		src;


	//dst.x = 50;
	//dst.y = 150;
	//dst.w = 384;
	//dst.h = 96;
	//rect_from_surface(app->assets.button_texture, &src);
	//blit_surface(app->assets.button_texture, &src, app->surface, &dst);
	//change_font(app, 48, 0xFF5F1E02);
	//render_text(app, (t_point){dst.x + dst.w / 2 - 96, dst.y + dst.h / 2 - 24}, "MENU");
//	change_font(app, 16, 0xFF111111);
	render_text(app, (t_point){100, 100}, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	render_text(app, (t_point){100, 120}, "abcdefghijklmnopqrstuvwxyz");
//	render_text(app, (t_point){260, 180}, "WORKING TITLE!");
//	change_font(app, 60, 0xFFC10020);
//	render_text(app, (t_point){224, 84}, "DOOM NUKEM:");
//	render_text(app, (t_point){264, 184}, "WORKING TITLE!");
//	change_font(app, 36, 0xFFFFFFFF);
//	render_text(app, (t_point){WIN_W / 2 - 5 * 36, WIN_H - 200}, "PRESS SPACE");
	load_font(app);
}
