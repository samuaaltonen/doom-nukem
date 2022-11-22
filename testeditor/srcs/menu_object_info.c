/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_object_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssulkuma <ssulkuma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:04:04 by ssulkuma          #+#    #+#             */
/*   Updated: 2022/11/21 16:27:46 by ssulkuma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doomnukem_editor.h"

/**
 * Renders object related texts on the help menu sidebar.
*/
static void	render_object_texts(t_app *app)
{
	int	pickable;
	int	mode;

	pickable = 0;
	mode = 0;
	change_font(app, 11, TEXT);
	render_text(app, (t_point){113, 120}, "MONSTER");
	render_text(app, (t_point){40, 140}, "HEALTH");
	render_text(app, (t_point){210, 140},"100");
	render_text(app, (t_point){40, 155}, "DAMAGE");
	render_text(app, (t_point){210, 155}, "10");
	if (pickable)
	{
		render_text(app, (t_point){50, 170}, "UNPICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){155, 170}, "- PICKABLE -");
	}
	else
	{
		render_text(app, (t_point){165, 170}, "PICKABLE");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){40, 170}, "- UNPICKABLE -");
	}
	change_font(app, 11, TEXT);
	if (mode == 1)
	{
		render_text(app, (t_point){121, 185}, "MOVES");
		render_text(app, (t_point){175, 185}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){35, 185}, "- IN PLACE -");
	}
	else if (mode == 2)
	{
		render_text(app, (t_point){45, 185}, "IN PLACE");
		render_text(app, (t_point){175, 185}, "FOLLOWS");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){111, 185}, "- MOVES -");
	}
	else
	{
		render_text(app, (t_point){45, 185}, "IN PLACE");
		render_text(app, (t_point){121, 185}, "MOVES");
		change_font(app, 11, ACTIVE_TEXT);
		render_text(app, (t_point){165, 185}, "- FOLLOWS -");
	}
	change_font(app, 15, TEXT);
}

/**
 * Renders the interaction menu on the help menu sidebar.
*/
static void	render_interaction_texts(t_app *app, int start_y)
{
	int		x;
	int		y;

	render_text(app, (t_point){10, start_y}, "INTERACTIONS");
	y = start_y + 20;
	while (y < start_y + 141)
	{
		x = 10;
		while (x < 270)
		{
			if (y == start_y + 20 || y % 15 == 0 || x == 10 || x == 269)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_ui_frame(app, (t_rect){10, start_y + 20 + (0 * 15), 260, 16}, 1, 0);
	change_font(app, 11, TEXT);
	render_text(app, (t_point){90, start_y + 25}, "NO INTERACTION");
	render_text(app, (t_point){100, start_y + 40}, "FLOOR HEIGHT");
	render_text(app, (t_point){90, start_y + 55}, "CEILING HEIGHT");
	render_text(app, (t_point){50, start_y + 70}, "FLOOR AND CEILING HEIGHT");
	render_text(app, (t_point){125, start_y + 85}, "SOUND");
	render_text(app, (t_point){110, start_y + 100}, "END LEVEL");
	render_text(app, (t_point){125, start_y + 115}, "LIGHT");
	render_text(app, (t_point){102, start_y + 130}, "TEXT POP-UP");
	change_font(app, 15, TEXT);
}

/**
* Renders object staticbars on the help menu sidebar.
*/
void	render_object_statics(t_app *app)
{
	int		x;
	int		y;

	y = 140;
	while (y < 250)
	{
		x = 100;
		while (x < 220)
		{
			if (x < 100 + 100 && y < 150)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			if (x < 10 + 100 && y > 153 && y < 163)
				put_pixel_to_surface(app->surface, x, y, TEXT);
			x++;
		}
		y++;
	}
	render_object_texts(app);
	render_interaction_texts(app, 220);
}

/**
 * Renders object icons on the help menu sidebar.
*/
void	render_object_icons(t_app *app, t_point point)
{
	t_rect		src;
	t_rect		icon;
	t_point		size;
	int			index;
	int			tex;
	int			object = 17;

	index = 0;
	while (index < 5)
	{
		if (index == 2)
		{
			size = (t_point){ICON_SIZE, ICON_SIZE};
			point.y -= 14;
		}
		else
			size = (t_point){ICON_SIZE / 2, ICON_SIZE / 2};
		tex = ICON_SIZE * ((index + object - 2) % (MAX_OBJECTS + 1));
		set_icon_rect(&src, (t_point){tex, 0}, size);
		set_icon_rect(&icon, point, size);
		blit_surface(app->assets.sprite, &src, app->surface, &icon);
		point.x += (ICON_SIZE / 2) + 10;
		if (index == 2)
		{
			point.x += (ICON_SIZE / 2);
			point.y += 14;
		}
		index++;
	}
}
