/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   title_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:05:46 by dpalacio          #+#    #+#             */
/*   Updated: 2022/10/25 15:04:49 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	title_screen(t_app *app)
{
	t_rect		src;
	t_rect		start_button;
	t_rect		levels_button;
	t_rect		options_button;
	t_rect		quit_button;

	change_font(app, 16, 0xFFFF9400);
	rect_from_surface(app->assets.button_idle, &src);
	start_button = render_button(app, (t_point){50, 200}, 2);
	render_text(app, (t_point){start_button.x + 24, start_button.y + 24}, "START GAME");
	levels_button = render_button(app, (t_point){50, 300}, 2);
	render_text(app, (t_point){levels_button.x + 24, levels_button.y + 24}, "CHOOSE LEVEL");
	options_button = render_button(app, (t_point){50, 400}, 2);
	render_text(app, (t_point){options_button.x + 24, options_button.y + 24}, "OPTIONS");
	quit_button = render_button(app, (t_point){50, 500}, 2);
	render_text(app, (t_point){quit_button.x + 24, quit_button.y + 24}, "QUIT GAME");
}