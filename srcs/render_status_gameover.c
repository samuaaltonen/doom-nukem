/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_gameover.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saaltone <saaltone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:22 by saaltone          #+#    #+#             */
/*   Updated: 2023/01/19 16:54:44 by saaltone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

/**
 * @brief Renders game over game state.
 * 
 * @param app 
 */
void	render_gameover(t_app *app)
{
	t_rect		dst;
	t_rect		src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	change_font(app, 80, BLACK);
	render_text(app, (t_rect){WIN_W / 2 - 120, 214, 320, 800}, "GAME OVER");
	change_font(app, 80, DARK_RED);
	render_text(app, (t_rect){WIN_W / 2 - 116, 210, 320, 800}, "GAME OVER");
	change_font(app, 32, WHITE);
	render_text(app, (t_rect){504, WIN_H - 170, 800, 800}, "You suck at this!");
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
}
