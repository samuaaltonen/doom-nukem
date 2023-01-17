/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:47:59 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/17 13:56:48 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_hand(t_app *app, int x, int y)
{
	t_rect	dst;
	t_rect	src;

	rect_from_surface(app->assets.weapon, &src);
	dst.x = x;
	dst.y = y;
	dst.w = src.w * 2;
	dst.h = src.h * 2;
	blit_surface(app->assets.weapon, &src, app->surface, &dst);
}