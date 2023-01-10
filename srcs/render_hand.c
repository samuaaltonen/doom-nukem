/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htahvana <htahvana@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:47:59 by htahvana          #+#    #+#             */
/*   Updated: 2023/01/05 18:59:32 by htahvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

void	render_hand(t_app *app, int x, int y)
{
	int nux;
	int texx;
	int texy;

	texx = 0;
	texy = 0;
	nux = x;
	while (++y < app->surface->h && texy < app->assets.weapon->h)
	{
		nux = x;
		texx = 0;
		while(++nux < app->surface->w && texx < app->assets.weapon->w)
		{
			int color = get_pixel_color(app->assets.weapon,texx,texy);
			if (color & 0xFF000000)
				put_pixel_to_surface(app->surface,nux,y,color);
			texx++;
		}
		texy++;
	}
}