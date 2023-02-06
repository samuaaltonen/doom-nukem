/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player_status.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:37:25 by dpalacio          #+#    #+#             */
/*   Updated: 2023/02/06 17:08:53 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	fill_meter(t_app *app, t_rect area, int type, int id);
static void	player_status_meter(t_app *app, t_rect area, int value, int color);
static void	energy_meter(t_app *app, t_rect area);

void	render_player_status(t_app *app)
{
	render_ui_element(app, app->assets.shield, (t_rect){32, 600, 32, 32});
	player_status_meter(app, (t_rect){80, 600, 16, 32},
		app->player.shield, CYAN);
	render_ui_element(app, app->assets.hp, (t_rect){32, 640, 32, 32});
	player_status_meter(app, (t_rect){80, 640, 16, 32},
		app->player.hp, DARK_RED);
	energy_meter(app, (t_rect){988, 592, 116, 24});
}

static void	player_status_meter(t_app *app, t_rect area, int value, int color)
{
	int	meter_value;
	int	i;

	meter_value = value;
	i = 4;
	while (i >= 0)
	{
		fill_meter(app, area, meter_value, color);
		area.x += 20;
		meter_value -= 40;
		i--;
	}
}

static void	energy_meter(t_app *app, t_rect area)
{
	int	x;
	int	y;

	render_ui_element(app, app->assets.energy, (t_rect){960, area.y, 24, 24});
	render_ui_frame(app, area, 1, DARK_GREY);
	area.x += 8;
	area.y += 8;
	area.w -= 16;
	area.h -= 16;
	x = area.x;
	y = area.y;
	while (y < area.y + area.h)
	{
		while (x < area.x + area.w)
		{
			if (x <= (area.x) + app->player.inventory.special_ammo / 2)
				put_pixel_to_surface(app->surface, x, y, GREEN);
			x++;
		}
		x = area.x;
		y++;
	}
}

static void	fill_meter(t_app *app, t_rect area, int value, int color)
{
	int	x;
	int	y;
	int	limit;

	x = area.x + area.w - 3;
	y = area.y + area.h - 3;
	if (value > 0)
		limit = (28.0 / 40.0) * value;
	else
		limit = 0;
	while (y >= area.y + 2 && limit > 0)
	{
		while (x >= area.x + 2)
		{
			put_pixel_to_surface(app->surface, x, y, color);
			x--;
		}
		x = area.x + area.w - 3;
		y--;
		limit--;
	}
	render_ui_element(app, app->assets.meter, area);
}
