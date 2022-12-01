/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:19:12 by dpalacio          #+#    #+#             */
/*   Updated: 2022/12/01 19:21:40 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void	ui_background(t_app *app,t_rect area, int size, int background);
static void ui_topframe(t_app *app,t_rect area, int size);
static void ui_midframe(t_app *app,t_rect area, int size);
static void ui_bottomframe(t_app *app,t_rect area, int size);
static void	fill_meter(t_app *app, t_rect area, int type, int id);
static void	player_status_meter(t_app *app, t_rect area, int value, int color);

/**
 * Renders all elements of the HUD
*/
void	render_ui(t_app *app)
{
	render_crosshair(app);
	render_text_prompt(app, (t_rect){10, 10, 112, 32}, 1, app->conf->fps_info);
	render_player_status(app);
	render_equipment(app);
	//----DEBUG FEATURE 
	if (app->conf->buttonstates & RIGHT_MOUSE)
		render_text_prompt(app, (t_rect){800, 150, 256, 64}, 1, "This is a nice and wonderful text prompt");
	//----
}

void	render_equipment(t_app *app)
{
	//----DEBUG FEATURE
	render_text_prompt(app, (t_rect){960, 624, 64, 64}, 1, "Q");
	render_ui_element(app, app->assets.pistol, (t_rect){960, 630, 64, 64});
	render_text_prompt(app, (t_rect){1040, 624, 64, 64}, 1, "E");
	render_ui_element(app, app->assets.pistol, (t_rect){1040, 630, 64, 64});
	//----
	hud_weapon(app, (t_rect){1120, 592, 128, 96});
}

void	hud_weapon(t_app *app, t_rect rect)
{
	int	i;

	i = 0;
	render_ui_frame(app, rect, 1, DARK_GREY);
	render_ui_element(app, app->assets.pistol, (t_rect){1152, 630, 64, 64});
	color_surface(app->assets.bullet, CYAN);
	rect.x += 16;
	rect.y += 16;
	rect.w = 4;
	rect.h = 8;
	while (i < app->player.equiped_weapon.magazine)
	{
		if (i >= app->player.equiped_weapon.ammo)
			color_surface(app->assets.bullet, GREY);
		render_ui_element(app, app->assets.bullet, rect);
		rect.x += 6;
		if (i >= app->player.equiped_weapon.ammo)
			color_surface(app->assets.bullet, GREY);
		i++;
	}
	change_font(app, 16, CYAN);
	render_text(app, (t_rect){1136, 626, 64, 64}, ft_itoa(app->player.inventory.ammo));
}

/**
 * Renders a ui frame with the background color given as parameter
*/	
void	render_ui_frame(t_app *app,t_rect area, int size, int background)
{
	if (background)
		ui_background(app, area, size, background);
	size *= 10;
	ui_topframe(app, area, size);
	ui_midframe(app, area, size);
	ui_bottomframe(app, area, size);
}

static void	ui_background(t_app *app,t_rect area, int size, int background)
{
	int	x;
	int	y;
	int top;
	int bottom;

	x = area.x;
	y = area.y;
	top = 8 * size;
	bottom = 0;
	while (y < area.y + area.h)
	{
		while (x < area.x + area.w)
		{
			if (x < area.x + area.w - top)
				put_pixel_to_surface(app->surface, x, y, background);
			x++;
		}
		top--;
		if (y >= area.y + area.h - 8 * size)
		{
			x = area.x + bottom;
			bottom++;
		}
		else
			x = area.x;
		y++;
	}
}

static void ui_topframe(t_app *app,t_rect area, int size)
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

static void ui_midframe(t_app *app,t_rect area, int size)
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

static void ui_bottomframe(t_app *app,t_rect area, int size)
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

t_rect	render_button(t_app *app, t_rect area, int size, char *text)
{
	t_rect	text_pos;

	change_font(app, 16, CYAN);
	text_pos.x = area.x + size * 12;
	text_pos.y = area.y + area.h / 2 - size * 12 / 2;
	text_pos.w = area.w;
	text_pos.h = area.h;
	if (!check_mouse(app, area))
		color_surface(app->assets.ui_frame, CYAN);
	else if (check_mouse(app, area))
	{
		change_font(app, 16, GREEN);
		if (((SDL_GetMouseState(NULL, NULL)) & SDL_BUTTON_LMASK) != 0)
			color_surface(app->assets.ui_frame, GREEN);
		else
		{
			color_surface(app->assets.ui_frame, DARK_RED);
			change_font(app, 16, DARK_RED);
		}		
	}
	render_ui_frame(app, area, size, 0);
	render_text(app, text_pos, text);
	load_font(app);
	color_surface(app->assets.ui_frame, CYAN);
	return (area);
}

void	render_text_prompt(t_app *app, t_rect area, int size, char *text)
{
	render_ui_frame(app, area, size, DARK_GREY);
	area.x += size * 12;
	area.y += size * 12;
	area.w -= size * 12;
	area.h -= size * 12;
	change_font(app, 16, CYAN);
	render_text(app, area, text);
	load_font(app);
}

void	render_pointer(t_app *app, int x, int y)
{
	t_rect		dst;
	t_rect		src;
	
	rect_from_surface(app->assets.pointer, &src);
	dst.x = x;
	dst.y = y;
	dst.w = app->assets.pointer->w;
	dst.h = app->assets.pointer->h;
	blit_surface(app->assets.pointer, &src, app->surface, &dst);
}
void	render_crosshair(t_app *app)
{
	t_rect	dst;
	t_rect	src;

	rect_from_surface(app->assets.crosshair, &src);
	dst.x = WIN_W / 2 - src.w / 2;
	dst.y = WIN_H / 2 - src.h / 2;
	dst.w = src.w;
	dst.h = src.h;
	blit_surface(app->assets.crosshair, &src, app->surface, &dst);
}

void	render_player_status(t_app *app)
{
	render_ui_element(app, app->assets.shield, (t_rect){32, 600, 32, 32});
	player_status_meter(app,(t_rect){80, 600, 16, 32}, app->player.shield, CYAN);
	render_ui_element(app, app->assets.hp, (t_rect){32, 640, 32, 32});
	player_status_meter(app,(t_rect){80, 640, 16, 32}, app->player.hp, DARK_RED);
}

static void	player_status_meter(t_app *app, t_rect area, int value, int color)
{
	int meter_value;
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

static void	fill_meter(t_app *app, t_rect area, int value, int color)
{
	int	x;
	int	y;
	int limit;

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

void	render_ui_element(t_app *app, SDL_Surface *elem, t_rect area)
{
	t_rect	src;

	rect_from_surface(elem, &src);
	blit_surface(elem, &src, app->surface, &area);
}

int	check_mouse(t_app *app, t_rect rect)
{
	if (app->mouse_pos.x >= rect.x
		&& app->mouse_pos.y >= rect.y
		&& app->mouse_pos.x <= (rect.x + rect.w)
		&& app->mouse_pos.y <= (rect.y + rect.h))
		return (1);
	return (0);
}
