/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/30 10:59:37 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

static void	ui_background(t_app *app, t_rect area, int size, int background);
static void	ui_topframe(t_app *app, t_rect area, int size);
static void	ui_midframe(t_app *app, t_rect area, int size);
static void	ui_bottomframe(t_app *app, t_rect area, int size);

void	render_ui_frame(t_app *app, t_rect area, int size, int background)
{
	if (background)
		ui_background(app, area, size, background);
	size *= 10;
	ui_topframe(app, area, size);
	ui_midframe(app, area, size);
	ui_bottomframe(app, area, size);
}

static void	ui_background(t_app *app, t_rect area, int size, int background)
{
	int		x;
	int		y;
	int		top;
	int		bottom;

	x = area.x - 1;
	y = area.y - 1;
	top = 8 * size;
	bottom = 0;
	while (++y < area.y + area.h)
	{
		while (++x < area.x + area.w)
		{
			if (x < area.x + area.w - top)
				put_pixel_to_surface(app->surface, x, y, background);
		}
		top--;
		if (y >= area.y + area.h - 8 * size)
		{
			x = area.x + bottom;
			bottom++;
		}
		else
			x = area.x;
	}
}

static void	ui_topframe(t_app *app, t_rect area, int size)
{
	t_rect	dst;
	t_rect	src;

	dst.x = area.x;
	dst.y = area.y;
	dst.w = size;
	dst.h = size;
	src.x = 0;
	src.y = 0;
	src.w = 10;
	src.h = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + size;
	dst.w = area.w - 2 * size;
	src.x = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + dst.w + size;
	dst.w = size;
	src.x = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
}

static void	ui_midframe(t_app *app, t_rect area, int size)
{
	t_rect	dst;
	t_rect	src;

	dst.x = area.x;
	dst.y = area.y + size;
	dst.h = area.h - 2 * size;
	src.x = 0;
	src.y = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + area.w - size;
	src.x = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
}

static void	ui_bottomframe(t_app *app, t_rect area, int size)
{
	t_rect	dst;
	t_rect	src;

	dst.x = area.x;
	dst.y = area.y + area.h - size;
	dst.w = size;
	dst.h = size;
	src.x = 0;
	src.y = 20;
	src.w = 10;
	src.h = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + size;
	dst.y = area.y + area.h - size;
	dst.w = area.w - 2 * size;
	src.x = 10;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
	dst.x = area.x + area.w - size;
	dst.y = area.y + area.h - size;
	dst.w = size;
	dst.h = size;
	src.x = 20;
	src.y = 20;
	blit_surface(app->assets.ui_frame, &src, app->surface, &dst);
}
