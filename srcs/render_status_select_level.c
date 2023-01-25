/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status_select_level.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <danielmdc94@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:59:18 by dpalacio          #+#    #+#             */
/*   Updated: 2023/01/25 13:40:45 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem.h"

static void select_level_button(t_app *app, t_rect button,
								void (*f)(t_app *app, int level), int level);
static int check_level(int n);
static void valid_levels(t_app *app);
static void make_button(t_app *app, int level);

void render_select_level(t_app *app)
{
	t_rect dst;
	t_rect src;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	rect_from_surface(app->assets.title_screen_image, &src);
	rect_from_surface(app->surface, &dst);
	blit_surface(app->assets.title_screen_image, &src, app->surface, &dst);
	render_ui_frame(app, (t_rect){320, 132, 324, 64}, 1, DARK_GREY);
	change_font(app, 32, DARK_RED);
	render_text(app, (t_rect){336, 146, 800, 800}, "SELECT LEVEL");
	render_ui_frame(app, (t_rect){320, 180, 640, 360}, 1, DARK_GREY);
	render_pointer(app, app->mouse_pos.x, app->mouse_pos.y);
	valid_levels(app);
	button_function(app,
		render_button(app, (t_rect){880, 488, 60, 32}, 1, "Back"),
		main_menu);
}

static void select_level_button(t_app *app, t_rect button,
								void (*f)(t_app *app, int level), int level)
{
	if (check_mouse(app, button))
	{
		if (app->conf->buttonstates & LEFT_MOUSE)
			start_timer(&app->button_timer, 0.5);
		else if (!(app->conf->buttonstates & LEFT_MOUSE)
			&& !check_timer(&app->button_timer))
		{
			f(app, level);
			start_timer(&app->button_timer, 0.0);
		}
	}
}

static void valid_levels(t_app *app)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		if (check_level(i))
			make_button(app, i);
		i++;
	}
}

static int check_level(int n)
{
	char *str;
	char *level;
	char *file;

	str = ft_strnew(sizeof(char) * 9);
	str = ft_strcpy(str, "level-");
	level = ft_itoa(n);
	file = ft_strcat(str, level);
	if (access(file, F_OK) == 0)
	{
		free(level);
		free(file);
		return (1);
	}
	free(level);
	free(file);
	return (0);
}

static void make_button(t_app *app, int level)
{
	t_rect	rect;

	if (level < 5)
	{	
		rect.x = 340;
		rect.y = 200 + 64 * level;
	}
	else if (level >= 5 && level < 10)
	{	
		rect.x = 534;
		rect.y = 200 + 64 * (level - 5);
	}
	
	rect.w = 160;
	rect.h = 32;
	select_level_button(app,
		render_button(app, rect, 1, "LEVEL 0"),
		import_change_level, level);
}